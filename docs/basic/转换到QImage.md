### 转换到QImage
Mat 对象默认获得的格式是BGR
所以我们需要用opencv自带的转换函数　：cvtColor(Mat source, Mat dst, ColorCOde)来转换成QImage正常读取的数据RGB格式。

```c++
Mat frame ;
capture>>frame;
Mat colorizedFrame;
cvtColor(frame,colorizedFrame,CV_BGR2RGB);
```

QImage初始化：

```c++
QImage img(frame.data,
  frame.size().width,
  frame.size().height,
  QImage::Format_RGB888);
```
好啦，转换完成，这样整个Mat对象的数据就可以正常在Qt控件中显示了！是不是很简单？
当然要深入了解整个函数的使用还有opencv所支持的格式转换就需要自行去官网文档查看了！这里就不一一列出来了。
