/*
接线说明:

程序说明:本实例用于演示如何使用WiFiServer库利用ESP32s3开发板建立基本网络服务器。
         以此获取客户端的请求信息,并通过串口输出相关的响应信息

注意事项:

函数示例:

作者:灵首

时间:202__

*/


#include <WiFiMulti.h>
#include <WiFi.h>
 
WiFiServer server(80);
WiFiMulti wifi_multi;  //建立WiFiMulti 的对象,对象名称是 wifi_multi



/*
# brief 连接WiFi的函数
# param 无
# retval 无
*/
void wifi_multi_con(void){
  int i=0;
  while(wifi_multi.run() != WL_CONNECTED){
    delay(1000);
    i++;
    Serial.print(i);
  }

}



/*
# brief 写入自己要连接的WiFi名称及密码,之后会自动连接信号最强的WiFi
# param 无
# retval  无
*/
void wifi_multi_init(void){
  wifi_multi.addAP("LINGSOU1029","12345678");
  wifi_multi.addAP("haoze1029","12345678");   //通过 wifi_multi.addAP() 添加了多个WiFi的信息,当连接时会在这些WiFi中自动搜索最强信号的WiFi连接
}


/*
# brief   运行服务器程序以检测客户端发送的请求并作出相应响应(串口输出客户端的请求信息)
# param 无
# retval  无
*/
void runServer(){
  //建立WiFiClient对象用于处理客户端请求信息
  WiFiClient incomingClient = server.available();
 
  // 如果没有客户端请求信息，则“跳过”函数中后续程序内容
  if (!incomingClient) {
    return;
  }
  
  Serial.println("====Client  Connected===\n");
 
  // 通过串口监视器输出客户端请求信息
  String clientRequest = incomingClient.readString();
  Serial.print(clientRequest);
 
// 建立服务器响应信息
  String httpResponse =
        "HTTP/1.0 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain;\r\n"
        "\r\n"
        "client_request_received";
 
  // 向客户端发送以上服务器响应信息
  incomingClient.print(httpResponse); 
 
  incomingClient.stop();  
  Serial.println("incomingClient stop\n");   
}



void setup() {
  //连接串口
  Serial.begin(9600);
  Serial.print("serial is OK\n");

  //wifi 连接设置
  wifi_multi_init();
  wifi_multi_con();
  Serial.print("wifi connected!!!\n");

  //输出连接信息(连接的WIFI名称及开发板的IP地址)
  Serial.print("connect wifi:");
  Serial.print(WiFi.SSID());
  Serial.print("\n");
  Serial.print("IP address:");
  Serial.print(WiFi.localIP());
  Serial.print("\n");

 
  // 启动服务器
  server.begin();
}
 
void loop() {
  runServer();  // 运行服务器
}
 
