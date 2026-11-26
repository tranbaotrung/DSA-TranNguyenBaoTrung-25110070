1. Thuật toán và Lý do thực tế:
  + Insertion Sort (Live Auction Monitor): Hiệu quả (độ phức tạp đạt O(N)) đối với dữ liệu gần như đã được sắp xếp sẵn, phù hợp xử lý luồng giá mới có chênh lệch nhỏ.
  + Selection Sort (Top-K Bid Finder): Trích xuất nhanh các phần tử lớn nhất chỉ sau vài vòng lặp đầu tiên mà không cần thêm bộ nhớ.
  + Interchange Sort (Price Anomaly Validator): Logic đơn giản, dễ cài đặt bộ đếm thao tác swap để phục vụ việc kiểm thử QA cho các lô dữ liệu nhỏ.
  + Bubble Sort Early Stop (Stabilization Detector): Dừng ngay ở vòng duyệt đầu tiên nếu không có swap, giúp phát hiện luồng cực kỳ nhanh.
  + Quick Sort (Full Historical Sorter): Có độ phức tạp O(N \log N), tốc độ nhanh, là lựa chọn tối ưu để sắp xếp hàng triệu bản ghi cuối ngày.
2. Runtime của Quick Sort trên 100k records:
  + Thời gian chạy đo được là: 121 ms.
3. Bug gặp phải và cách xử lý:
  + Lỗi: Bị báo lỗi "Không tìm thấy file" khi sinh file test 100k dòng.
  + Chẩn đoán & Xử lý: LLM chỉ ofstream không thể tự tạo thư mục.Em đã dùng lệnh mkdir test_data trong Terminal để tạo thư mục trước, sau đó file large.txt đã được sinh ra thành công.
4. Các Prompt đã dùng với LLM:
  + [Green] "Hãy cho tôi 5 bộ dữ liệu đầu vào thuộc trường hợp biên (edge-case) cần cân nhắc khi kiểm thử."
  + [Green] "Giải thích tại sao hàm quickSortWrapper lại cần thiết."
  + [Yellow] "Lỗi mismatch types std::min ở dòng 50 là gì và đổi thành kiểu nào cho đúng?"
5. Độ phức tạp trường hợp xấu nhất của Quick Sort (Median-of-three):
  + O(N^2). Lý do là vì dù đã chọn trung vị của 3 phần tử, trong một số mẫu dữ liệu rất đặc thù hoặc mảng có quá nhiều phần tử trùng lặp giống hệt nhau, thuật toán vẫn có thể phân hoạch mảng thành 2 phần mất cân bằng (một bên 0 phần tử, một bên N-1 phần tử) qua từng vòng đệ quy.
