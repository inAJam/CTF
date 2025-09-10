# droids1
We launch the apk in android studio.  
![alt text](image-1.png)  
From the ctf we know that we need to find the ***pass*** to get the flag. Since it looks like the apk was built with debugging enabled, we look at the resources and we find the password in the **string** section.  
![alt text](image-2.png)  
We enter the password in the emulator and get the flag.  
![alt text](image.png)  
Flag: **picoCTF{pining.for.the.fjords}**