import cv2
import serial,time

#cascade to detect face
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
#obtain default webcam
cap = cv2.VideoCapture(0)
#width of the video
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 960) 
#height of the video
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 540)
#identify the arduino on com port
ArduinoSerial = serial.Serial('com3',9600,timeout=0.1)
time.sleep(1)

while cap.isOpened():

    #read the image
    ret, frame= cap.read()
    #turn image to gray
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    #detect the face
    faces= face_cascade.detectMultiScale(gray,1.1,6)  
    for x,y,w,h in faces:
        #send coordinates to Arduino
        string='X{0:d}Y{1:d}'.format((x+w//2),(y+h//2))
        print(string)
        #set x and y coordinates to arduino
        ArduinoSerial.write(string.encode('utf-8'))
        #plot the center of the face where the nose is located
        cv2.circle(frame,(x+w//2,y+h//2),2,(0,255,0),2)
        #plot the rectangle
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),3)

    #show the frame on an application
    cv2.imshow('facedetection',frame)

    # press q to quit
    if cv2.waitKey(10)&0xFF== ord('q'):
        break
cap.release()
cv2.destroyAllWindows()