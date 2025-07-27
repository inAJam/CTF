## Obedient Cat
For this challenge, we just download the file and **cat** it to get the flag.  
Flag: **picoCTF{s4n1ty_v3r1f13d_4a2b35fd}**  


## Super SSH
For this challenge, we just need to ssh inot the given serverwith the given command.  
***ssh ctf-player@titan.picoctf.net -p57347***  
Flag: **picoCTF{s3cur3_c0nn3ct10n_45a48857}**  


## what's a net cat?
We just **netcat** into the server and get the flag.  
Flag: **picoCTF{nEtCat_Mast3ry_d0c64587}**  


## Warmed Up
**0x3D=61**  
Flag: **picoCTF{61}**  


## 2Warm
**42->101010**
Flag: **picoCTF{101010}**  


## Bases
For this, we jsut need to decode this base64 string.  
Flag: **picoCTF{l3arn_th3_r0p35}**


## Wave a flag
If we look into the downloaded file, we find that it's a **ELF executable**. We give it the necessary permissions for execution and then the program itself guides us to the flag.  
![alt text](images/image.png)  
Flag: **picoCTF{b1scu1ts_4nd_gr4vy_f0668f62}**  


## Tab, Tab, Attack
We just use the **tab-completion** to get to the execuatble after unziping it. When we run the executable, we get the flag.  
FLag: **picoCTF{l3v3l_up!_t4k3_4_r35t!_d32e018c}**  


## Insp3ct0r
We open the webpage and look at the html for the code, there we find the first third of the flag ***picoCTF{tru3_d3***.  
![alt text](images/image-1.png)  
We then go to the **sylesheet** and **js** pages linked at the top of the html to find the other parts.  
![alt text](images/image-2.png)  
![alt text](images/image-3.png)  
Flag: **picoCTF{tru3_d3t3ct1ve_0r_ju5t_lucky?2e7b23e3}**  


## strings it
We use the **strings** command to search the file and then pipe it through **grep** to find the flag.  
Flag: **picoCTF{5tRIng5_1T_7f766a23}**  


## First Grep
Same as above, we use **strings** and **grep** to get the flag.  
Flag: **picoCTF{grep_is_good_to_find_things_dba08a45}**  


## where are the robots
Adding **robots.txt** at the end of the **url** gets us a list of disallowed webpages. Navigating to those webpages, gives us the flag.  
![alt text](images/image-4.png)  
![alt text](images/image-5.png)  
Flag: **picoCTF{ca1cu1at1ng_Mach1n3s_1bb4c}**  


## Python Wrangling
We run the file with the given options and then enter the required password to get the flag.  
![alt text](images/image-6.png)  
Flag: **picoCTF{4p0110_1n_7h3_h0us3_dbd1bea4}**  


## PW Crack 1
We can just open the python file and see that there is a check for the user password.  
![alt text](images/image-7.png)  
Once we run the file and enter the password, we get the flag.  
![alt text](images/image-8.png)  
Flag: **picoCTF{545h_r1ng1ng_56891419}**  


## PW Crack 2
Same as above, we examine the code and just convert the line ***chr(0x64) + chr(0x65) + chr(0x37) + chr(0x36)*** into normal ascii, then type it to get the flag.  
![alt text](images/image-9.png)  
Flag: **picoCTF{tr45h_51ng1ng_489dea9a}**  


## Big Zip
Once we unzip it we realise that it's a really big directory with many folders and files. We use **grep** to search for **pico** inside this directory.  
![alt text](images/image-10.png)  
Flag: **picoCTF{gr3p_15_m4g1c_ef8790dc}**