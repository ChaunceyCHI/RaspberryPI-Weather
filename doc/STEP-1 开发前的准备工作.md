
硬件准备：    
- Raspberry PI 4B    
- 大于等于36G的存储卡（我的是64G）  
- 读卡器  
软件准备：    
- [Raspberry Pi Image ](https://www.raspberrypi.com/software/)  

将存储卡插入读卡器，将读卡器连接至电脑。在进行下一步操作时，务必备份存储卡内文件。在之后的镜像写入过程中，将会抹去存储卡内所有数据。  

**使用管理员方式**打开 Raspberry Pi Image 程序，选择 `CHOOSE DEVICE` 内的 `Raspberry Pi 4` ，点击后会自动返回上一级界面，点击 `选择操作系统` ，这里我选择的是 `RASPBERRY PI 4 (64-BIT)`，同样，点击后会返回上一级界面。此处选择你的存储卡，然后点击下一步。    
![Step_1](http://pic.chaunceychi.fun/100-Project/QWeather%26RaspberryPI/Step1/Step1_01.png)

接下来选择编辑设置，配置树莓派的相关配置文件。这里可以设置通过浏览器访问的树莓派的域名、用户名和密码（SSH访问时也会用到），WIFI信息等。  
![Step_2](http://pic.chaunceychi.fun/100-Project/QWeather%26RaspberryPI/Step1/Step1_02.png)
注意，若要使用SSH功能（一般都会用到），则需要在`SERVICE`选项卡中勾选`开启SSH服务`选项。  
![Step_3](http://pic.chaunceychi.fun/100-Project/QWeather%26RaspberryPI/Step1/Step1_03.png)
点击`保存`后点击`是`。  
![Step_4](http://pic.chaunceychi.fun/100-Project/QWeather%26RaspberryPI/Step1/Step1_04.png)
提示将会抹去全部内容的提示，再次点击`是`即可启动刷写。  
![Step_5](http://pic.chaunceychi.fun/100-Project/QWeather%26RaspberryPI/Step1/Step1_05.png)
刷写过程中我没有遇到什么错误情况。如果有朋友按照上面步骤操作，遇到了错误情况，请在本文下方进行留言，或者发送邮件到 c_x@ik.me 与我交流探讨。  

刷写完成后，将存储卡插入树莓派并上电。  

我是通过网口，直接将树莓派接入路由器，以此达到接入网络的目的。如不想通过此方式接入，请自行搜索网络教程，或等待后续的文档更新（我也不确定会不会更新）。  

可以在cmd中通过`ping raspberrypi.local`的方式来验证树莓派是否正常接入网络。  
![Step_6](http://pic.chaunceychi.fun/100-Project/QWeather%26RaspberryPI/Step1/Step1_06.png)

未总结的后续步骤：  
[用Windows远程桌面连接树莓派（详细教程）_windows远程树莓派桌面-CSDN博客](https://blog.csdn.net/weixin_43624626/article/details/104227725)  

[树莓派安装clash，实现科学上网 | 麦田里的熊 (panda74.fun)](https://blog.panda74.fun/blog/practice/raspi/clash)  

