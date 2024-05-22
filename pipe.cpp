#include "pipe.h" // Bao gồm tệp tiêu đề cho lớp pipe.
#include "stdio.h" // Bao gồm thư viện chuẩn C cho việc nhập xuất.

vector<position> posPipe; // Khai báo một vector để lưu trữ vị trí của các ống.

bool pipe::init() // Hàm khởi tạo cho lớp pipe.
{
    posPipe.clear(); // Xóa tất cả các vị trí hiện tại trong vector, chuẩn bị cho việc khởi tạo mới.
    for (signed char i = 0; i < TOTAL_PIPE; i++) // Lặp qua số lượng ống tối đa.
    {
        position temp; // Tạo một biến tạm thời để lưu trữ vị trí của từng ống.
        temp.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE + 350, (rand() % (randMax - randMin + 1)) + randMin); // Đặt vị trí ngẫu nhiên cho ống dựa trên giá trị ngẫu nhiên.
        posPipe.push_back(temp); // Thêm vị trí ống vào vector.
    }
    if (isNULL()) // Kiểm tra xem đối tượng có chưa được khởi tạo không.
    {
        if (Load( "res/image/pipe.png", 1 )) // Tải hình ảnh ống từ đường dẫn.
        {
            return true; // Trả về true nếu tải thành công.
        }
    }
    return false; // Trả về false nếu không tải được hình ảnh.
}

void pipe::Free() // Hàm giải phóng tài nguyên.
{
    free(); // Gọi hàm giải phóng tài nguyên tổng thể.
}

void pipe::render() // Hàm vẽ ống lên màn hình.
{
    for (signed char i = 0; i < TOTAL_PIPE; i++) // Lặp qua tất cả các ống.
    {
        if (posPipe[i].x <= SCREEN_WIDTH && posPipe[i].x > -getWidth()) // Kiểm tra xem ống có nằm trong phạm vi màn hình không.
        {
            Render(posPipe[i].x, posPipe[i].y); // Vẽ ống phía trên.
        }
        Render(posPipe[i].x, posPipe[i].y + getHeight() + PIPE_SPACE, 180); // Vẽ ống phía dưới (đã xoay 180 độ).
    }
}

void pipe::update() // Hàm cập nhật vị trí của các ống.
{
    if (!die) // Nếu trò chơi vẫn đang diễn ra.
    {
        for (signed char i = 0; i < TOTAL_PIPE; i++) // Lặp qua tất cả các ống.
        {
            if (posPipe[i].x < - getWidth()) // Kiểm tra nếu ống đã di chuyển ra ngoài màn hình bên trái.
            {
                posPipe[i].y = (rand() % (randMax - randMin + 1)) + randMin; // Đặt lại vị trí y ngẫu nhiên cho ống.
                posPipe[i].x = posPipe[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE; // Đặt lại vị trí x cho ống, dựa vào vị trí của ống cuối cùng.
            }
            else
            {
                posPipe[i].x -= 3; // Di chuyển ống sang trái.
            }
        }
    }
}
