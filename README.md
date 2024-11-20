# Hệ thống tưới cây tự động thông minh
## Nội dung chính 
Hệ thống sẽ tự động tưới cây khi độ ẩm đất giảm xuống dưới mức cài đặt. Hệ thống cũng cho phép người dùng theo dõi và điều khiển quá trình tưới từ xa qua một bảng điều khiển web (Node-RED Dashboard), sử dụng giao thức MQTT để trao đổi dữ liệu giữa ESP32 và máy tính hoặc điện thoại thông minh. Cảm biến độ ẩm sẽ cung cấp dữ liệu thời gian thực về tình trạng đất, và người dùng có thể điều chỉnh cài đặt hoặc xem báo cáo qua bảng điều khiển.
## Sơ đồ khối dự kiến 
![sodokhoi](https://github.com/user-attachments/assets/413d188a-f51a-41fa-b935-5a3963a7f89f)

## Đặt vấn đề bài toán
Vấn đề thực tế là trong nông nghiệp đô thị hoặc tại các khu vực có diện tích cây trồng nhỏ, việc tự động tưới cây thường xuyên mà không cần người chăm sóc là rất cần thiết. Hệ thống này giải quyết bài toán tưới cây tự động khi đất quá khô, giúp tiết kiệm nước và công sức khi mà mọi người không thể luôn dành thời gian cho việc tưới nước và khu vực khó khăn để tưới, đồng thời đảm bảo cây trồng luôn nhận đủ lượng nước cần thiết, một vấn đề khá thiết thực trong nông nghiệp thông minh.
## Các chức năng chính:
-  Tự động tưới cây: Khi độ ẩm đất dưới mức cài đặt, ESP32 sẽ kích hoạt bơm nước,buzzer để báo hiệu tín hiệu kích hoạt.
-  Theo dõi từ xa: Người dùng có thể theo dõi trạng thái hệ thống (độ ẩm đất, trạng thái bơm nước) qua Node-RED Dashboard.
-  Điều khiển từ xa: Người dùng có thể tắt/mở hệ thống tưới cây từ thiết bị thông minh kết nối internet.
