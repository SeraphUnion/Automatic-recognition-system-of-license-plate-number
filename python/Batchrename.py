#_*_coding:utf-8
import os
import cv2
pic_path="/home/just_sort/CLionProjects/zxybisepredeal/python/train_images/training-set/chinese-characters/1"

def rename():
    piclist=os.listdir(pic_path)
    total_num=len(piclist)

    i=1
    for pic in piclist:
        if pic.endswith(".jpg") | pic.endswith(".png"):
            old_path=os.path.join(os.path.abspath(pic_path),pic)
            new_path=os.path.join(os.path.abspath(pic_path),'000'+format(str(i),'0>3')+'.jpg')
           # pic = cv2.resize(pic, dsize=(224,224), interpolation=cv2.INTER_LINEAR)
            os.renames(old_path,new_path)
            img = cv2.imread(new_path)
            img = cv2.resize(img, dsize=(32,40), interpolation=cv2.INTER_CUBIC)
            cv2.imwrite(new_path, img)
            print (u"把原图片命名格式："+old_path+u"转换为新图片命名格式："+new_path)
            #print "把原图片路径：%s,转换为新图片路径：%s" %(old_path,new_path)
            i=i+1

    print ("总共"+str(total_num)+"张图片被重命名为:" "000001.jpg~"+'000'+format(str(i-1),'0>3')+".jpg形式")

rename()