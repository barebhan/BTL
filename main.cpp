/*
Đoạn mã này mô tả luồng điều khiển và xử lý các sự kiện chính trong trò chơi, bao gồm việc xử lý đầu vào,
cập nhật và hiển thị các thành phần của trò chơi, và quản lý trạng thái như tạm dừng và chơi lại.
*/
#include "game.h" // Bao gồm tệp tiêu đề cho lớp game.
#include "lib.h" // Bao gồm thư viện tự định nghĩa.
#include <time.h> // Bao gồm thư viện cho các hàm liên quan đến thời gian.
#include <stdlib.h> // Bao gồm thư viện chuẩn cho các hàm chung.
#include <SDL.h> // Bao gồm thư viện SDL chính để quản lý cửa sổ và sự kiện.
#include <SDL_image.h> // Bao gồm thư viện SDL_image để xử lý hình ảnh.
#include <SDL_ttf.h> // Bao gồm thư viện SDL_ttf để xử lý phông chữ.

const short int FPS = 60; // Định nghĩa số khung hình trên giây.
const short int frameDelay = 1000 / FPS; // Tính toán độ trễ giữa các khung hình để đạt FPS mong muốn.

using namespace std;

int main(int argc, char** argv) // Hàm main, điểm bắt đầu của chương trình.
{
    Uint32 frameStart; // Biến lưu thời gian bắt đầu của mỗi khung hình.
    short int frameTime; // Biến lưu thời gian xử lý mỗi khung hình.
    game g; // Khởi tạo đối tượng game.
    bool isMenu = 0; // Biến trạng thái menu.
    bool isPause = 0; // Biến kiểm tra trạng thái tạm dừng.
    bool isSound = 1; // Biến kiểm tra trạng thái âm thanh.
    bool isDark = 0; // Biến kiểm tra chủ đề tối.

    while(!g.isQuit()) // Vòng lặp chính của trò chơi chạy đến khi người dùng muốn thoát.
    {
        frameStart = SDL_GetTicks(); // Ghi nhận thời điểm bắt đầu của khung hình.

        if (g.isDie()) // Kiểm tra nếu nhân vật trong game đã chết.
        {
            if (isMenu) {
                g.sound.playHit(); // Phát âm thanh va chạm nếu đang trong menu.
                g.character.render(); // Hiển thị nhân vật.
            }
            g.userInput.Type = game::input::NONE; // Đặt lại kiểu nhập của người dùng.
            while(g.isDie() && !g.isQuit()) // Xử lý khi nhân vật chết nhưng game chưa thoát.
            {
                g.takeInput(); // Xử lý nhập liệu từ người dùng.
                if (isMenu == 1 && g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isMenu = 0; // Thoát menu nếu người dùng chọn chơi lại.
                    }
                    g.userInput.Type = game::input::NONE;
                }
                if (!isDark) g.renderBackground(); // Hiển thị hình nền thông thường.
                else g.renderBackgroundNight(); // Hiển thị hình nền chế độ đêm.
                g.pipe.render(); // Hiển thị các ống.
                g.land.render(); // Hiển thị mặt đất.
                if (isMenu)
                {
                    g.character.render(); // Hiển thị nhân vật.
                    g.character.fall(); // Xử lý rơi của nhân vật.
                    g.renderGameOver(); // Hiển thị màn hình game over.
                    g.renderMedal(); // Hiển thị huy chương.
                    g.renderScoreSmall(); // Hiển thị điểm nhỏ.
                    g.renderBestScore(); // Hiển thị điểm cao nhất.
                    g.replay(); // Hiển thị nút chơi lại.
                }
                else
                {
                    g.pipe.init(); // Khởi tạo lại các ống.
                    g.character.init(isDark); // Khởi tạo lại nhân vật dựa trên chủ đề.
                    g.character.render(); // Hiển thị nhân vật.
                    g.renderMessage(); // Hiển thị thông điệp.
                    if (g.userInput.Type == game::input::PLAY)
                    {
                        g.Restart(); // Khởi động lại trò chơi.
                        isMenu = 1;
                        g.userInput.Type = game::input::NONE;
                    }
                    g.land.update(); // Cập nhật mặt đất.
                }
                g.display(); // Hiển thị khung hình lên màn hình.
            }
            g.pipe.init(); // Khởi tạo lại các ống.
        }
        else
        {
            g.takeInput(); // Xử lý nhập liệu từ người dùng.

            if (g.userInput.Type == game::input::PAUSE)
            {
                isPause = abs(1 - isPause); // Đảo trạng thái tạm dừng.
                g.userInput.Type = game::input::NONE;
            }

            if (isPause == 0 && g.userInput.Type == game::input::PLAY)
            {
                if (isSound) g.sound.playBreath(); // Phát âm thanh thở nếu âm thanh được bật.
                g.character.resetTime(); // Đặt lại thời gian cho nhân vật.
                g.userInput.Type = game::input::NONE;
            }

            if (!isDark) g.renderBackground(); // Hiển thị hình nền thông thường.
            else g.renderBackgroundNight(); // Hiển thị hình nền chế độ đêm.
            g.pipe.render(); // Hiển thị các ống.
            g.land.render(); // Hiển thị mặt đất.
            g.character.render(); // Hiển thị nhân vật.
            g.renderScoreLarge(); // Hiển thị điểm lớn.

            if (!isPause)
            {
                g.character.update(g.getPipeWidth(), g.getPipeHeight()); // Cập nhật nhân vật với kích thước ống.
                g.pipe.update(); // Cập nhật các ống.
                g.land.update(); // Cập nhật mặt đất.
                g.pause(); // Hiển thị trạng thái tạm dừng.
            }
            else
            {
                g.resume(); // Tiếp tục trò chơi.
                g.renderPauseTab(); // Hiển thị tab tạm dừng.
                g.renderScoreSmall(); // Hiển thị điểm nhỏ.
                g.renderBestScore(); // Hiển thị điểm cao nhất.
                g.replay(); // Hiển thị nút chơi lại.
                g.sound.renderSound(); // Hiển thị biểu tượng âm thanh.
                if (!isDark) g.lightTheme(); else g.darkTheme(); // Thay đổi chủ đề sáng/tối.
                g.nextButton(); // Hiển thị nút tiếp theo.
                if (g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isPause = 0; // Đặt trạng thái tạm dừng là không.
                    }
                    else if (g.sound.checkSound())
                    {
                        isSound = abs(1 - isSound); // Đảo trạng thái âm thanh.
                    }
                    else if (g.changeTheme())
                    {
                        isDark = abs(1 - isDark); // Đảo chủ đề sáng/tối.
                        g.character.init(isDark); // Khởi tạo lại nhân vật theo chủ đề mới.
                    }
                    g.userInput.Type = game::input::NONE;
                }
            }
            g.display(); // Hiển thị khung hình lên màn hình.
        }
        frameTime = SDL_GetTicks() - frameStart; // Tính thời gian xử lý khung hình.
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime); // Đợi đến khi đủ thời gian của một khung hình.
        }
    }
    return 0; // Kết thúc chương trình.
}
