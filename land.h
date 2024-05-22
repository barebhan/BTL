#pragma once // Đảm bảo rằng file header này chỉ được include một lần trong quá trình biên dịch.

#include "lib.h" // Bao gồm các định nghĩa chung và thư viện cần thiết từ file lib.h.
#include <vector> // Bao gồm thư viện chuẩn C++ cho container vector.

using namespace std; // Sử dụng không gian tên std để truy cập các tính năng chuẩn dễ dàng hơn.

// Lớp land kế thừa từ LTexture.
class land : LTexture
{
public:
    bool init(); // Phương thức khởi tạo mặt đất, tải texture và thiết lập vị trí ban đầu.

    void Free(); // Phương thức giải phóng tài nguyên, đặc biệt là texture.

    void render(); // Phương thức vẽ mặt đất lên màn hình.

    void update(); // Phương thức cập nhật vị trí của mặt đất để tạo hiệu ứng di chuyển.

private:
    position posLand; // Biến lưu vị trí hiện tại của mặt đất trên màn hình.
};
/*
bool init(): Phương thức này khởi tạo mặt đất bằng cách tải texture mặt đất và thiết lập vị trí ban đầu của nó dựa trên kích thước màn hình và chiều cao mặt đất.
             Ví dụ, vị tríd có thể được đặt ở cuối màn hình để mặt đất luôn hiển thị ở dưới cùng.
void Free(): Phương thức này được gọi để giải phóng tài nguyên liên quan đến mặt đất, chủ yếu là giải phóng texture mà nó sử dụng.
             Điều này rất quan trọng để tránh rò rỉ bộ nhớ khi không còn sử dụng đối tượng mặt đất.
void render(): Phương thức này sử dụng để vẽ mặt đất lên màn hình tại vị trí được chỉ định bởi posLand.
               Vị trí này có thể thay đổi theo thời gian nếu có cập nhật di chuyển, chẳng hạn như cuộn màn hình.
void update(): Phương thức này cập nhật vị trí của mặt đất để tạo hiệu ứng di chuyển,
                ví dụ như cuộn mặt đất liên tục khi nhân vật chính di chuyển qua màn hình. Điều này giúp tạo ra một cảm giác chuyển động trong trò chơi.

Lớp land là một phần quan trọng trong việc tạo bối cảnh và môi trường trò chơi, cung cấp mặt đất ổn định cho nhân vật di chuyển và tương tác.
*/
