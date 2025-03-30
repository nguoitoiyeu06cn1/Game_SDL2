# Game_SDL2

## Giới thiệu

Đây là một phiên bản game Rắn săn mồi cổ điển được viết bằng C++ sử dụng thư viện SDL2. Game có nhiều cấp độ khó khác nhau, rắn AI, âm thanh và hệ thống tính điểm.

## Tính năng

*   **Gameplay cổ điển:** Điều khiển rắn ăn thức ăn để lớn lên, tránh va chạm với các enemy AI snake.
*   **Rắn AI:** Các rắn AI di chuyển xung quanh bản đồ, tăng thêm độ khó cho game.
*   **Nhiều cấp độ:** Chọn từ nhiều cấp độ khác nhau, mỗi cấp độ có số lượng rắn AI khác nhau.
*   **Hệ thống tính điểm:** Tích lũy điểm bằng cách ăn thức ăn và cố gắng đạt điểm cao nhất.
*   **Âm thanh:** Hiệu ứng âm thanh khi ăn thức ăn và nhạc nền tạo không khí cho game.
*   **Điều khiển:** Sử dụng các phím mũi tên hoặc chuột để điều khiển rắn.
*   **Lưu điểm cao:** Lưu trữ điểm cao nhất của người chơi.

## Ảnh chụp màn hình 
  ![Screenshot 2025-03-30 160743](https://github.com/user-attachments/assets/68dfe066-0ec9-4324-9084-87a49c99f09e)
  ![Screenshot 2025-03-30 160743](https://github.com/user-attachments/assets/96da83b3-b4e3-429c-a44b-ce15ea331116)
  ![Screenshot 2025-03-30 160506](https://github.com/user-attachments/assets/d46bcd4e-297a-4595-b32f-8425c66e3c84)
  ![Screenshot 2025-03-30 173353](https://github.com/user-attachments/assets/ddfe5be5-4bbb-49d4-b256-284af4da9a23)


  


## Yêu cầu

*   SDL2 (phiên bản 2.0.x trở lên)
*   SDL2\_ttf (phiên bản 2.0.x trở lên)
*   Trình biên dịch C++ (ví dụ: GCC, Clang, MSVC)

## Hướng dẫn cài đặt

1.  **Cài đặt SDL2 và SDL2\_ttf:**

    *   **Trên Windows:**
        *   Tải các file thư viện SDL2 và SDL2\_ttf từ trang chủ của SDL.
        *   Giải nén các file thư viện vào một thư mục nào đó (ví dụ: `C:\SDL2`).
        *   Thêm đường dẫn đến thư mục chứa các file `.dll` vào biến môi trường `PATH`.
        *   Copy các file `.dll` vào thư mục chứa file thực thi của game.

    *   **Trên Linux (Ubuntu/Debian):**

        ```bash
        sudo apt-get update
        sudo apt-get install libsdl2-dev libsdl2-ttf-dev
        ```

    *   **Trên macOS:**

        *   Cài đặt Homebrew (nếu chưa có): `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
        *   Cài đặt SDL2 và SDL2\_ttf: `brew install sdl2 sdl2_ttf`

2.  **Clone repository:**

    ```bash
    git clone https://github.com/nguoitoiyeu06cn1/Game_SDL2.git
    cd Game_SDL2
    ```


3.  **Biên dịch game:**

    *   **Sử dụng Code::Blocks:**
        *   Mở file project `.cbp` trong Code::Blocks.
        *   Chọn "Build" -> "Build" hoặc "Build" -> "Rebuild".

    *   **Sử dụng dòng lệnh (ví dụ: GCC):**
        *   Di chuyển đến thư mục chứa các file mã nguồn.
        *   Chạy lệnh sau (điều chỉnh tùy theo các file và thư viện bạn sử dụng):

            ```bash
            g++ -o snake main.cpp AIsnake.cpp food.cpp graphics.cpp level.cpp menu.cpp render.cpp snake.cpp utils.cpp -lSDL2 -lSDL2_ttf
            ```

4.  **Chạy game:**

    *   Sau khi biên dịch thành công, chạy file thực thi (ví dụ: `game.exe` trên Windows, `./game` trên Linux/macOS).

## Cách chơi

*   Sử dụng các phím mũi tên (hoặc chuột) để điều khiển rắn di chuyển.
*   Ăn thức ăn để lớn lên và tăng điểm.
*   Tránh va chạm với tường, chính bản thân rắn và các rắn AI.
*   Chọn cấp độ khó khác nhau để tăng thử thách.

## Điều khiển

*   **Phím mũi tên lên:** Di chuyển lên
*   **Phím mũi tên xuống:** Di chuyển xuống
*   **Phím mũi tên trái:** Di chuyển trái
*   **Phím mũi tên phải:** Di chuyển phải
*   **Chuột:** Điều khiển hướng di chuyển của rắn (nếu tính năng này được bật)
*   **Phím SPACE:** Tạm dừng game
*   **Phím R:** Chơi lại game
*   **Phím ESCAPE (trong menu chọn level):** Thoát game

## Tác giả

*   Phạm Ngọc Dũng


