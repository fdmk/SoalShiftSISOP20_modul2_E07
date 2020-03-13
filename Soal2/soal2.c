#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <stdbool.h>
#include <curl/curl.h> //untuk download

int main(){
    //====>> membuat daemon (untuk membuat folder setiap 30 dektik)
    pid_t pid,sid; //varibel untuk menyimpan PID
    pid=fork(); //meyimpan pid dari child process

    //jika gagal
    if(pid<0){
        exit(EXIT_FAILURE);
    }
    //jika berhasil
    if(pid>0){
        exit(EXIT_SUCCESS);
    }

    umask(0); //mendapatkan akses full dari file daemon yang dibuat

    sid=setsid(); //suapaya tidak menjadi orphan process
    
    //membuat process menjadi independen
    if(sid<0){
        exit(EXIT_FAILURE);
    }
    if((chdir("/home/basuki/code_test/tugmod2_sisop/")) < 0){
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    //mulai program daemon
    while(true){
        //--->> bagian A, membuat folder

        //membuat char untuk menyimpan nama folder dengan format waktu
        char Time_dir[50];//untuk nama directory
        char Time_img[50];//untuk nama image
        
        ///waktu
        //mengambil waktu sekarang
        time_t t=time(NULL);
        struct tm tm=*localtime(&t);

        //memasukkan waktu kedalam char Time_dir
        sprintf(Time_dir,"%d-%02d-%02d_%02d:%02d:%02d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
                
        //char untuk directory penyimpanan directory baru
        char dir[50]={"/home/basuki/code_test/tugmod2_sisop/"};
        
        //untuk mkdir
        int check;
        
        //make directory
        check= mkdir(strcat(dir,Time_dir),0777);
    
        //change directory
        chdir(Time_dir);
            //perror("chdir() to directory failed");

        //--->> bagian B, download
        CURL *curl;
        int result;

        //membuat variabel epoch unix
        long int now_epoch;
        int size_phot;

        //membuat file untuk menyimpan hasil download
        FILE *fp;

        char *url="https://i.picsum.photos/id/";
        char img[50];//sebagai penyimpan sting link

        //download
        curl=curl_easy_init();
        for(int foto_id=1;foto_id<=20;foto_id++)
        {
            ///waktu
            //mengambil waktu sekarang
            time_t t=time(NULL);
            struct tm tm=*localtime(&t);

            //memasukkan waktu kedalam char Time_img sebagai nama image
            sprintf(Time_img,"%d-%02d-%02d_%02d:%02d:%02d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
            
            //time epoch
            time_t epoch_now=time(NULL);

            //mengubah ukuran berdasarkan epoch time
            now_epoch=epoch_now;
            size_phot=(now_epoch%1000)+100;

            //memberikan nama link
            sprintf(img,"%s%d/%d/%d.jpg",url,foto_id,size_phot,size_phot);

            //memberikan nama image dengan timestamp
            fp=fopen(strcat(Time_img,".jpg"), "wb");

            printf("%s\n",img);
            
            //proses download
            curl_easy_setopt(curl, CURLOPT_URL,img);
            curl_easy_setopt(curl,CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl,CURLOPT_FAILONERROR, 1L);

            result= curl_easy_perform(curl);
                if(result==CURLE_OK)
                {
                    printf("Download Successful!\n");
                }
                else
                {
                    printf("Error: %s\n",curl_easy_strerror(result));
                }
            fclose(fp);
            sleep(5);
        }
        curl_easy_cleanup(curl);

        //kembali ke directory sebelumya
        chdir("..");

        //untuk zip
        pid_t zip;
        zip=fork();

        //membuat zip
        wait(NULL);
        if(zip==0)
        {        
            char *zip[]={"zip","-r",Time_dir,Time_dir,NULL};
                execv("/bin/zip", zip);
        }
        
        remove(Time_dir);//delete directory

        sleep(30);
    }
}
