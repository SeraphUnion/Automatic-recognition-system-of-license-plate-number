此系统为本人毕业设计时所做的课题，解决的主要是蓝底白字的车牌号码的识别。在车牌检测和定位阶段参考了EasyPR的思路，
利用了HSV颜色空间和Sobel算子进行了车牌定位，没有用到CMser 定位是比较遗憾的。<br>
本文的研究内容为：<br>
一、研究利用车牌颜色信息对图片或视频中的车牌区域进行定位<br>
二、研究利用车牌边缘信息对图片或视频中的车牌区域进行定位<br>
三、研究利用SVM算法对定位到的车牌区域和干扰区域进行分类<br>
四、研究利用c++代码能力和思维对车牌区域的7个字符进行切割<br>
五、研究利用深度学习中的卷积神经网络识别车牌上的每个字符 <br>
六、研究利用跨平台架构库wxWidgets为系统设计良好的用户界面<br>

整个系统的开发流程如下： <br>
![image](https://github.com/BBuf/Automatic-recognition-system-of-license-plate-number/blob/master/Screenshots/1.png)<br>
整个系统的前端界面如下：<br>
![image](https://github.com/BBuf/Automatic-recognition-system-of-license-plate-number/blob/master/Screenshots/2.png)<br>
系统新增用户错误反馈功能如下：<br>
![image](https://github.com/BBuf/Automatic-recognition-system-of-license-plate-number/blob/master/Screenshots/3.png)<br>
![image](https://github.com/BBuf/Automatic-recognition-system-of-license-plate-number/blob/master/Screenshots/4.png)<br>

研究成果和展望：<br>
1、本系统利用颜色信息和边缘信息可以检测自然环境下95%以上车牌完好的蓝底白字车牌，并且车牌字符的识别准确率可以达到80%以上，
且利用用户的错误反馈信息可以不断的自主学习提高车牌识别率。 <br>
2、但是本系统仍旧存在一些不足，当车牌为黄底黑字的教练车型时车牌的检测率会降低，以及出现纯蓝色车身的蓝底白字车牌时会出现
检测不到车牌情况，仍需要进一步研究。 <br>
3、本系统仍处于实验室研究阶段，但只要给予训练的车牌号码数量足够多并且解决了上述两个问题后，可以应用在实际场景中进行车牌号码
自动识别的工作。<br>

运行条件分析：<br>
本系统运行在windows操作系统中，用户在克隆下这个工程后可以直接利用CLION来启动，整个工程用了相对路径所以不用考虑不兼容的问题，用户
启动这个工程之后需要进行一次模型训练就是点击前端界面中字符识别模型训练下的字符识别模型训练和汉字识别模型训练即可，除了下载一个IDEA
用户不需要配置任何环境，即可运行本系统和在本系统的基础上修改和学习相关代码。里面的Commons文件夹将所有需要用到的opencv的插件和wxWidgets
插件都便宜成了.a文件，cmakelists里面直接引用了，用户可以不用配置任何环境，用Clion打开就可以运行本工程。并且我提供了一个本工程的懒人版，
克隆下来点击window.exe启动系统，然后点击模型训练训练自己的模型即可，因为不同电脑的cpu和gpu不同，所以需要自己训练一次模型再来识别。
https://github.com/BBuf/License-plate-number-automatic-identification-system-laziness-Edition<br>
