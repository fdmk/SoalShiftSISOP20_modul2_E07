#include <stdio.h>//intuk int dan sebagainya
#include <wait.h>// untuk mengambil nilai waktu
#include <time.h>//untuk melakukan wait process
#include <string.h>//untuk string
#include <stdbool.h>//untuk perulangan
#include <curl/curl.h>//untuk download
#include <stdlib.h>// untuk EXIT_FAILURE & EXIT_SUCCESS
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>//untuk fungsi umask dan mkdir
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>// untuk STDIN_FILENO || STDOUT_FILENO || STDERR_FILENO

int main(){
     //====>> membuat daemon
            pid_t pid;//variabel untuk menyimpan PID
            pid_t sid;//varibel unuk menyimpan SID
            //menyiapkan variabel-variabel sebagai proses untuk pembuatan 
            pid_t point_b;
            pid_t point_a;
            pid_t sudo;

            pid=fork(); //menyimpan PID dari child

            //jika gagal
            if(pid<0){
                exit(EXIT_FAILURE);
            }

            //jika berhasil
            if(pid>0){
                exit(EXIT_SUCCESS);
            }
            
            umask(0);//mendapatkan akses penuh dari process yang dibuat

            sid=setsid();//mencegah process child menjadi process orphan

            //menjadikan process independen
            if(sid<0){
                exit(EXIT_FAILURE);
            }
            if(chdir("/home/basuki/code_test/tugmod2_sisop/")<0){
                exit(EXIT_FAILURE);
            }

            close(STDIN_FILENO);//menutup akses input keyboard kedalam process
            close(STDOUT_FILENO);//menutup akses output untuk menapilkan process ke layar
            close(STDERR_FILENO);//menutup akses peringatan error kepengguna

    //mulai program daemon
    while(true){

        sudo=fork();
        wait(NULL);
        if(sudo==0)
        {
            char Time_dir[50];//untuk nama directory
            char Time_img[50];//untuk nama image

            long int now_epoch;//variabel penyimpan nilai epoch time
            int size_phot;//variabel penyimpan ukuran foto berdasarkan epoch time

            //sebagai penyimpan workdirectory
            char dir[50]={"/home/basuki/code_test/tugmod2_sisop/"};
        
            char *url="https://i.picsum.photos/id/";
            char link[50];//penyimpan link akhir

            //mengambil waktu
            time_t t=time(NULL);
            struct tm tm=*localtime(&t);

            //memasukkan timestamp kedalam Time_dir
            sprintf(Time_dir,"%d-%02d-%02d_%02d:%02d:%02d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
        
            ///===>>> PERSIAPAN DOWNLOAD
            //persiapan untuk membuat file hasil download image
            FILE *fp;
            //mengambil dari library lcurl.h
            CURL *curl;
            int result;

            //pembuatan point a
            point_a=fork();
            wait(NULL);//menyelesaikan dulu proses child

            //pembuatan point a
            if(point_a == 0){
                mkdir(strcat(dir,Time_dir),0777);
            }

            else
            {        
                //pembuatan point b
                point_b=fork();
                wait(NULL);

                if(point_b<0)
                {exit(EXIT_FAILURE);}
                
                if(point_b==0);
                {
                    //change directory
                    chdir(Time_dir);
                    
                    //download
                    curl=curl_easy_init();
                    for(int id_foto=1;id_foto<=20;id_foto++)
                    {
                        //mengambil dari time untuk nama image
                        time_t T=time(NULL);
                        struct tm TM=*localtime(&T);

                        //memasukkan time kedalam variabel Time_img
                        sprintf(Time_img,"%d-%02d-%02d_%02d:%02d:%02d",TM.tm_year,TM.tm_mon,TM.tm_mday,TM.tm_hour,TM.tm_min,TM.tm_sec);

                        //time epoch unix
                        time_t epoch_now=time(NULL);

                        //mengubah ukuran berdasarkan epoch time
                        now_epoch=epoch_now;
                        size_phot=(now_epoch%1000)+100;
                        
                        //melengkapkan link yang diberikan
                        sprintf(link,"%s%d/%d/%d.jpg",url,id_foto,size_phot,size_phot);

                        //membuat file hasil download sekagus dengan memberikan nama image
                        fp=fopen(strcat(Time_img,".jpg"), "wb");

                        //proses download
                        curl_easy_setopt(curl,CURLOPT_URL,link);
                        curl_easy_setopt(curl,CURLOPT_WRITEDATA, fp);
                        curl_easy_setopt(curl,CURLOPT_FAILONERROR, 1L);

                        curl_easy_perform(curl);
                        fclose(fp);
                        sleep(5);
                    }
                    curl_easy_cleanup(curl);

                    //kembali ke directory sebelumnya
                    chdir("..");

                    ///Bagian C
                    //untuk zip
                    pid_t point_c;// untuk penyelesaian pont c;
                    point_c=fork();

                    //membuat zip
                    wait(NULL);
                    if(point_c==0)
                    {
                        //membuat zip dengan format [nama_zip].zip [nama_file(yang akan dicompress)]
                        char *compress[]={"zip","-r",Time_dir,Time_dir,NULL};
                            execv("/bin/zip", compress);
                    }
                    else
                    {
                        remove(Time_dir);//delete directory
                    }
                }
            }
        }
        
        else
        {
            sleep(30);
        }
    }
}
