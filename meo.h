#pragma once // Đảm bảo rằng file header này chỉ được include một lần trong quá trình biên dịch.

#include "lib.h" // Bao gồm các định nghĩa chung và thư viện cần thiết từ file lib.h.
#include "pipe.h" // Bao gồm định nghĩa của lớp pipe để có thể tương tác với các ống trong trò chơi.

using namespace std; // Sử dụng không gian tên std để dễ dàng truy cập các tính năng chuẩn.

// Lớp meo, kế thừa từ lớp LTexture.
class meo : LTexture
{
public:
    bool init(bool isDark); // Khởi tạo nhân vật, với tham số xác định chế độ tối hoặc sáng.

    void render(); // Vẽ nhân vật lên màn hình.

    void Free(); // Giải phóng các tài nguyên liên quan đến nhân vật.

    void resetTime() // Đặt lại thời gian, sử dụng để kiểm soát logic rơi hoặc nhảy.
    {
        time = 0;
    }

    void fall(); // Xử lý logic rơi của nhân vật.

    void update(short int pileWidth, short int pileHeight); // Cập nhật trạng thái và vị trí của nhân vật dựa trên các ống trên màn hình.

private:
    short int angle, time, x0; // angle: góc xoay của nhân vật; time: thời gian tính từ khi bắt đầu rơi; x0: vị trí ban đầu khi bắt đầu rơi.
    short int ahead = 0; // Chỉ số của ống phía trước mà nhân vật đang tiến tới.
    string saved_path = ""; // Đường dẫn lưu ảnh nhân vật hiện tại.
    position posMeo; // Vị trí hiện tại của nhân vật trên màn hình.
};
/*bool init(bool isDark): Phương thức này khởi tạo nhân vật mèo, tải hình ảnh tương ứng với chế độ sáng hoặc tối dựa trên tham số isDark.
Nếu isDark là true, nhân vật sẽ sử dụng hình ảnh dành cho bối cảnh tối.
void render(): Phương thức này sử dụng để vẽ nhân vật lên màn hình tại vị trí hiện tại được lưu trong posMeo và với góc xoay hiện tại angle.
void Free(): Giải phóng tài nguyên đồ họa mà nhân vật sử dụng, đảm bảo không có rò rỉ bộ nhớ khi trò chơi kết thúc hoặc nhân vật được tạo lại.
void resetTime(): Đặt lại bộ đếm thời gian, thường được gọi khi nhân vật bắt đầu một hành động mới như nhảy hoặc rơi.
void fall(): Xử lý lôgic cho việc nhân vật rơi xuống. Phương thức này sẽ tính toán vị trí mới của nhân vật dựa trên thời gian rơi và góc hiện tại.
void update(short int pileWidth, short int pileHeight): Cập nhật trạng thái của nhân vật dựa vào kích thước của các ống (pileWidth và pileHeight).
Phương thức này kiểm tra va chạm và cập nhật vị trí và trạng thái của nhân vật.
Lớp meo là một thành phần quan trọng trong trò chơi, quản lý hình ảnh, vị trí, và hành vi của nhân vật chính, bao gồm cả việc nhảy và rơi giữa các ống trên màn hình.
*/
