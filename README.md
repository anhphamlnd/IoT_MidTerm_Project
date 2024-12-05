# Hệ thống tưới cây tự động thông minh đơn giản
## Nội dung chính
Hệ thống sẽ tự động tưới cây khi độ ẩm đất giảm xuống dưới mức cài đặt. Hệ thống cũng cho phép người dùng theo dõi và điều khiển quá trình tưới từ xa qua một bảng điều khiển web (Node-RED Dashboard), sử dụng giao thức MQTT để trao đổi dữ liệu giữa ESP32 và máy tính hoặc điện thoại thông minh. Cảm biến độ ẩm sẽ cung cấp dữ liệu thời gian thực về tình trạng đất, và người dùng có thể điều chỉnh cài đặt hoặc xem báo cáo qua bảng điều khiển.

## Sơ đồ khối dự kiến
![image](https://github.com/user-attachments/assets/ff418450-a248-4b19-9e28-861a7e07d48b)


## Đặt vấn đề bài toán
Vấn đề thực tế là trong nông nghiệp đô thị hoặc tại các khu vực có diện tích cây trồng nhỏ, việc tự động tưới cây thường xuyên mà không cần người chăm sóc là rất cần thiết. Hệ thống này giải quyết bài toán tưới cây tự động khi đất quá khô, giúp tiết kiệm nước và công sức khi mà mọi người không thể luôn dành thời gian cho việc tưới nước và khu vực khó khăn để tưới, đồng thời đảm bảo cây trồng luôn nhận đủ lượng nước cần thiết, một vấn đề khá thiết thực trong nông nghiệp thông minh.

## Các chức năng chính:
Tự động tưới cây: Khi độ ẩm đất dưới mức cài đặt, ESP32 sẽ kích hoạt bơm nước,buzzer để báo hiệu tín hiệu kích hoạt.
Theo dõi từ xa: Người dùng có thể theo dõi trạng thái hệ thống (độ ẩm đất, trạng thái bơm nước) qua Node-RED Dashboard.
Điều khiển từ xa: Người dùng có thể tắt/mở hệ thống tưới cây từ thiết bị thông minh kết nối internet.

## Demo

Vì thiếu thốn các vật cần thiết nên trong bài tập này,em chỉ demo ở chế độ đơn giản nhất bằng việc sử dụng cốc nước để biểu thị độ ẩm của đất

Hình ảnh demo trường hợp độ khô trên 80%
![image](https://github.com/user-attachments/assets/e8078255-7fc4-4253-9bd9-05c7979ed408)

Lúc này relay ON và bơm hoạt động,có thể thấy vòi bơm nước đang chảy

Hình ảnh demo trường hợp độ khô dưới 80%
![image](https://github.com/user-attachments/assets/c192857a-4e43-40c8-858a-8f20c70de657)

Lúc này relay OFF và ngắt hoạt động,có thể thấy vòi bơm nước không hoạt động
## Dashboard
![image](https://github.com/user-attachments/assets/ba7c8a29-e13f-494e-adaa-681461fcca35)

### Hình này biểu diễn độ khô của đất,vì đang ở chế độ demo nên em coi trường hợp cảm biến độ ẩm đất ở ngoài không khí là mặc định 100% là khô.Ảnh minh họa là ảnh mà em đưa cảm biến vào bên trong nước
- Node-red em hiển thị 2 chế độ hoạt động là thủ công và tự động
    + Trong trường hợp người dùng muốn chuyển sang chế độ bật tắt relay thì chỉ cần bấm nút thủ công và bật tắt bình thường.
    + Trong trường hợp người dùng muốn chuyển sang chế độ tự động thì chỉ cần bấm nút tự động và nếu độ khô trên 80% thì relay sẽ bật và máy bơm hoạt động.Vì em mới chỉ setup để demo nên em đang coi là 80%,
    + tùy với loại cây tương thích mà sẽ điều chỉnh cho phù hợp

## Note: Trong phần code,em có đang để Soil Moisture là nhưng trên thực tế em sử dụng thì em đang coi đây là độ khô của đất nên có thể gây ra sự nhầm lẫn.
