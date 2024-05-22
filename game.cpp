// Thêm các thư viện và tệp tiêu đề cần thiết vào chương trình.
#include "game.h"
#include "lib.h"
#include <iostream>

// Định nghĩa phương thức để lấy và xử lý đầu vào từ người dùng.
void game::takeInput()
{
    while(SDL_PollEvent(&event) != 0) // Vòng lặp kiểm tra các sự kiện đầu vào.
    {
        if (event.type == SDL_QUIT) // Nếu sự kiện là yêu cầu thoát.
        {
            userInput.Type = input::QUIT; // Đặt loại đầu vào là QUIT.
            quit = true; // Đặt cờ thoát là true.
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN && // Nếu nhấn chuột hoặc phím
            (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0) )
        {
            userInput.Type = input::PLAY; // Đặt loại đầu vào là PLAY.
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0) // Nếu nhấn ESC
        {
            userInput.Type = input::PAUSE; // Đặt loại đầu vào là PAUSE.
        }
    }
}

// Hàm khởi tạo của lớp game.
game::game()
{
    initGraphic(); // Khởi tạo đồ họa.
    pipe.init(); // Khởi tạo ống.
    land.init(); // Khởi tạo mặt đất.
    sound.init(); // Khởi tạo âm thanh.
}

// Hàm hủy của lớp game.
game::~game()
{
    character.Free(); // Giải phóng nhân vật.
    pipe.Free(); // Giải phóng ống.
    land.Free(); // Giải phóng mặt đất.
    sound.Free(); // Giải phóng âm thanh.
    free(); // Giải phóng bộ nhớ.
    releaseGraphic(); // Giải phóng đồ họa.
}

// Hàm giải phóng tài nguyên đồ họa.
void game::releaseGraphic()
{
    SDL_DestroyWindow(gWindow); // Hủy cửa sổ.
    gWindow = NULL; // Đặt lại con trỏ cửa sổ là NULL.
    SDL_DestroyRenderer(gRenderer); // Hủy bộ kết xuất.
    gRenderer = NULL; // Đặt lại con trỏ bộ kết xuất là NULL.
    IMG_Quit(); // Thoát khỏi thư viện IMG.
    TTF_Quit(); // Thoát khỏi thư viện TTF.
    SDL_Quit(); // Thoát khỏi SDL.
}

// Hàm khởi tạo đồ họa cho trò chơi.
bool game::initGraphic()
{
    bool success = true; // Biến cờ kiểm tra thành công.

    if (SDL_Init(SDL_INIT_VIDEO) < 0) // Khởi tạo SDL cho đồ họa video.
    {
        printf("SDL could not initialize! ", SDL_GetError()); // In lỗi nếu không khởi tạo được.
        success = false; // Đặt thành công là false.
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) // Đặt chất lượng kết xuất.
        {
            printf("Warning: Linear texture filtering not enabled!"); // Cảnh báo nếu không kích hoạt bộ lọc texture.
        }

        gWindow = SDL_CreateWindow("Flappy Cat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); // Tạo cửa sổ mới.

        if (gWindow == NULL) // Kiểm tra nếu cửa sổ không được tạo.
        {
            printf("Window could not be created! ", SDL_GetError()); // In lỗi nếu tạo cửa sổ không thành công.
            success = false; // Đặt thành công là false.
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Tạo bộ kết xuất.

            if (gRenderer == NULL) // Kiểm tra nếu bộ kết xuất không được tạo.
            {
                printf("Renderer could not be created! ", SDL_GetError()); // In lỗi nếu tạo bộ kết xuất không thành công.
                success = false; // Đặt thành công là false.
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // Đặt màu vẽ mặc định.

                int imgFlags = IMG_INIT_PNG; // Cờ khởi tạo ảnh PNG.
                if (!(IMG_Init(imgFlags) & imgFlags)) // Khởi tạo thư viện ảnh và kiểm tra.
                {
                    printf("SDL_image could not initialize! ", IMG_GetError()); // In lỗi nếu thư viện ảnh không khởi tạo được.
                    success = false; // Đặt thành công là false.
                }

                if (TTF_Init() == -1) // Khởi tạo thư viện phông chữ TTF.
                {
                    printf("SDL_ttf could not initialize! ", TTF_GetError()); // In lỗi nếu thư viện TTF không khởi tạo được.
                    success = false; // Đặt thành công là false.
                }
            }
        }
    }

    return success; // Trả về trạng thái thành công của việc khởi tạo đồ họa.
}

// Hàm hiển thị nội dung lên màn hình.
void game::display()
{
    SDL_RenderPresent(gRenderer); // Cập nhật nội dung lên màn hình.
    SDL_RenderClear(gRenderer); // Xóa màn hình để chuẩn bị cho khung hình tiếp theo.
}
// Hàm hiển thị điểm số nhỏ
void game::renderScoreSmall()
{
    string s = to_string(score); // Chuyển điểm số hiện tại thành chuỗi.
    signed char len = s.length(); // Lấy độ dài của chuỗi điểm.
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.

    for (signed char i = len - 1; i >= 0; i--) // Vòng lặp qua từng chữ số của điểm số.
    {
        signed char number = s[i] - '0'; // Chuyển ký tự chữ số thành giá trị số nguyên.
        if (number == 1) // Nếu chữ số là 1.
        {
            image.Load("res/number/small/1.png", scaleNumberS); // Tải hình ảnh tương ứng.
        }
        // Tương tự, kiểm tra và tải hình ảnh cho các chữ số từ 2 đến 9 và 0.
        else if (number == 2) { image.Load("res/number/small/2.png", scaleNumberS); }
        else if (number == 3) { image.Load("res/number/small/3.png", scaleNumberS); }
        else if (number == 4) { image.Load("res/number/small/4.png", scaleNumberS); }
        else if (number == 5) { image.Load("res/number/small/5.png", scaleNumberS); }
        else if (number == 6) { image.Load("res/number/small/6.png", scaleNumberS); }
        else if (number == 7) { image.Load("res/number/small/7.png", scaleNumberS); }
        else if (number == 8) { image.Load("res/number/small/8.png", scaleNumberS); }
        else if (number == 9) { image.Load("res/number/small/9.png", scaleNumberS); }
        else { image.Load("res/number/small/0.png", scaleNumberS); }
        image.Render(260 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 268); // Hiển thị ảnh.
    }
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị điểm số lớn
void game::renderScoreLarge()
{
    string s = to_string(score); // Chuyển điểm số hiện tại thành chuỗi.
    signed char len = s.length(); // Lấy độ dài của chuỗi điểm.
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.

    for (signed char i = 0; i < len; i++) // Vòng lặp qua từng chữ số của điểm số.
    {
        signed char number = s[i] - '0'; // Chuyển ký tự chữ số thành giá trị số nguyên.
        // Tương tự như trên, tải và hiển thị hình ảnh tương ứng cho từng chữ số.
        if (number == 1) { image.Load("res/number/large/1.png", 1); }
        else if (number == 2) { image.Load("res/number/large/2.png", 1); }
        else if (number == 3) { image.Load("res/number/large/3.png", 1); }
        else if (number == 4) { image.Load("res/number/large/4.png", 1); }
        else if (number == 5) { image.Load("res/number/large/5.png", 1); }
        else if (number == 6) { image.Load("res/number/large/6.png", 1); }
        else if (number == 7) { image.Load("res/number/large/7.png", 1); }
        else if (number == 8) { image.Load("res/number/large/8.png", 1); }
        else if (number == 9) { image.Load("res/number/large/9.png", 1); }
        else { image.Load("res/number/large/0.png", 1); }
        image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100); // Hiển thị ảnh.
    }
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị điểm số tốt nhất đã lưu
void game::renderBestScore()
{
    ifstream fileIn("res/data/bestScore.txt"); // Mở tệp để đọc điểm số tốt nhất.
    fileIn >> bestScore; // Đọc điểm số tốt nhất.
    ofstream fileOut("res/data/bestScore.txt", ios::trunc); // Mở tệp để ghi điểm số mới.

    if (score > bestScore) // Kiểm tra nếu điểm hiện tại cao hơn điểm tốt nhất.
    {
        bestScore = score; // Cập nhật điểm tốt nhất.
    }
    string s = to_string(bestScore); // Chuyển điểm tốt nhất thành chuỗi.
    signed char len = s.length(); // Lấy độ dài của chuỗi điểm.
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.

    for (signed char i = len-1; i >= 0; i--) // Vòng lặp qua từng chữ số của điểm tốt nhất.
    {
        signed char number = s[i] - '0'; // Chuyển ký tự chữ số thành giá trị số nguyên.
        // Tương tự như trên, tải và hiển thị hình ảnh tương ứng cho từng chữ số.
        if (number == 1) { image.Load("res/number/small/1.png", scaleNumberS); }
        else if (number == 2) { image.Load("res/number/small/2.png", scaleNumberS); }
        else if (number == 3) { image.Load("res/number/small/3.png", scaleNumberS); }
        else if (number == 4) { image.Load("res/number/small/4.png", scaleNumberS); }
        else if (number == 5) { image.Load("res/number/small/5.png", scaleNumberS); }
        else if (number == 6) { image.Load("res/number/small/6.png", scaleNumberS); }
        else if (number == 7) { image.Load("res/number/small/7.png", scaleNumberS); }
        else if (number == 8) { image.Load("res/number/small/8.png", scaleNumberS); }
        else if (number == 9) { image.Load("res/number/small/9.png", scaleNumberS); }
        else { image.Load("res/number/small/0.png", scaleNumberS); }
        image.Render(260 - image.getWidth()*(len-i-1)*0.75 - 5*(len - i - 1), 315); // Hiển thị ảnh.
    }
    image.free(); // Giải phóng bộ nhớ của texture.

    fileOut << bestScore; // Ghi điểm tốt nhất vào tệp.
    fileIn.close(); // Đóng tệp đọc.
    fileOut.close(); // Đóng tệp ghi.
}
// Hàm hiển thị thông điệp mở đầu hoặc hướng dẫn
void game::renderMessage()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/message.png", 1); // Tải hình ảnh thông điệp từ tệp.
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180); // Hiển thị hình ảnh tại vị trí giữa màn hình, theo chiều ngang.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị nền ban ngày
void game::renderBackground()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/background.png", 1); // Tải hình ảnh nền ban ngày từ tệp.
    image.Render(0, 0); // Hiển thị hình ảnh nền ở góc trên cùng bên trái của màn hình.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị nền ban đêm
void game::renderBackgroundNight()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/background-night.png", 1); // Tải hình ảnh nền ban đêm từ tệp.
    image.Render(0, 0); // Hiển thị hình ảnh nền ở góc trên cùng bên trái của màn hình.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị mặt đất
void game::renderLand()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/land.png", 1); // Tải hình ảnh mặt đất từ tệp.
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT - image.getHeight()); // Hiển thị hình ảnh mặt đất ở phía dưới màn hình, giữa theo chiều ngang.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm tiếp tục trò chơi
void game::resume()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/resume.png", 1); // Tải hình ảnh nút tiếp tục từ tệp.
    image.Render(SCREEN_WIDTH - 50, 20); // Hiển thị nút tiếp tục ở góc trên cùng bên phải của màn hình.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm tạm dừng trò chơi
void game::pause()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/pause.png", 1); // Tải hình ảnh nút tạm dừng từ tệp.
    image.Render(SCREEN_WIDTH - 50, 20); // Hiển thị nút tạm dừng ở góc trên cùng bên phải của màn hình.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị tab tạm dừng
void game::renderPauseTab()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/pauseTab.png", 1); // Tải hình ảnh tab tạm dừng từ tệp.
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230); // Hiển thị tab tạm dừng tại vị trí giữa màn hình theo chiều ngang.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị chủ đề sáng
void game::lightTheme()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/meo.png", 0.8); // Tải hình ảnh chủ đề sáng từ tệp.
    image.Render(105, 315); // Hiển thị hình ảnh chủ đề ở vị trí cụ thể trên màn hình.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị chủ đề tối
void game::darkTheme()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/meo-night.png", 0.8); // Tải hình ảnh chủ đề tối từ tệp.
    image.Render(105, 315); // Hiển thị hình ảnh chủ đề ở vị trí cụ thể trên màn hình.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị các nút điều hướng cho chủ đề
void game::nextButton()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/nextRight.png", 1); // Tải hình ảnh nút mũi tên phải từ tệp.
    image.Render(149, 322); // Hiển thị nút mũi tên phải ở vị trí cụ thể trên màn hình.
    image.Load("res/image/nextLeft.png", 1); // Tải hình ảnh nút mũi tên trái từ tệp.
    image.Render(88, 322); // Hiển thị nút mũi tên trái ở vị trí cụ thể trên màn hình.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm kiểm tra sự thay đổi chủ đề khi người dùng nhấp vào nút
bool game::changeTheme()
{
    int x, y; // Khai báo biến để lưu vị trí con trỏ chuột.
    SDL_GetMouseState(&x, &y); // Lấy trạng thái hiện tại của chuột.
    if (((x > 149 && x < 149+13)  || (x > 88 && x < 88 + 13)) && (y > 322 && y < 322 + 16)) // Kiểm tra nếu chuột nằm trong vùng nút.
    {
        return true; // Trả về true nếu chuột nhấp vào nút.
    }
    return false; // Trả về false nếu không.
}
// Hàm hiển thị màn hình "Game Over"
void game::renderGameOver()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/gameOver.png", 1); // Tải hình ảnh "Game Over" từ tệp.
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150); // Hiển thị hình ảnh tại vị trí giữa màn hình, theo chiều ngang.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị huy chương dựa trên điểm số của người chơi
void game::renderMedal()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.

    if (score > 10 && score <= 20) // Kiểm tra điểm số để xác định loại huy chương.
    {
        image.Load("res/medal/silver.png", scaleNumberS); // Tải huy chương bạc nếu điểm từ 10 đến 20.
    }
    else if (score > 20) // Nếu điểm số lớn hơn 20.
    {
        image.Load("res/medal/gold.png", scaleNumberS); // Tải huy chương vàng.
    }
    else // Nếu điểm số dưới hoặc bằng 10.
    {
        image.Load("res/medal/bronze.png", scaleNumberS); // Tải huy chương đồng.
    }
    image.Render(83, 275); // Hiển thị huy chương ở vị trí cụ thể trên màn hình.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm hiển thị nút "Chơi lại"
void game::replay()
{
    LTexture image; // Tạo đối tượng texture để hiển thị hình ảnh.
    image.Load("res/image/replay.png", 1); // Tải hình ảnh nút "Chơi lại" từ tệp.
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380); // Hiển thị nút tại vị trí giữa màn hình, theo chiều ngang.
    image.free(); // Giải phóng bộ nhớ của texture.
}

// Hàm kiểm tra xem người dùng có nhấp vào nút "Chơi lại" không
bool game::checkReplay()
{
    int x, y; // Khai báo biến để lưu vị trí con trỏ chuột.
    SDL_GetMouseState(&x, &y); // Lấy trạng thái hiện tại của chuột.
    if (x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 380 && y < 380 + 60) // Kiểm tra nếu chuột nằm trong vùng nút "Chơi lại".
    {
        return true; // Trả về true nếu chuột nhấp vào nút.
    }
    return false; // Trả về false nếu không.
}

// Hàm khởi động lại trò chơi
void game::Restart()
{
    die = false; // Đặt lại trạng thái "chết" của nhân vật là false.
    score = 0; // Đặt lại điểm số là 0.
    character.resetTime(); // Gọi hàm reset thời gian của đối tượng nhân vật.
}
