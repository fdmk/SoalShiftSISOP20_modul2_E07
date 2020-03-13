# SoalShiftSISOP20_modul2_E07
2. A. ![soal 2A](https://user-images.githubusercontent.com/61625353/76606273-8d3d2e80-6544-11ea-8766-c16cf232d46a.PNG)
Di soal 2 kita diminta untuk membuat sebuah folder khusus, di dalamnya terdapat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss]. Pertama, kita membuat char untuk menyimpan nama folder dengan format waktu. Lalu, kita menggunakan struct untuk mengambil current time. kemudian waktu dimasukkan ke dalam char Time_dir, kemudian membuat char untuk penyimpanan directory baru.
2. B. ![soal2b_1](https://user-images.githubusercontent.com/61625353/76607628-dc845e80-6546-11ea-8e5d-f51082472506.PNG)
![soal2b_2](https://user-images.githubusercontent.com/61625353/76607662-eefe9800-6546-11ea-9440-b1e38edca090.PNG)
Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYYmm- dd_HH:ii:ss]. Penjelasan untuk soal ini sudah tertera pada comment source code
2. C. ![soal2c](https://user-images.githubusercontent.com/61625353/76607956-68968600-6547-11ea-9071-ad4e338b9c19.PNG)
Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip). Penjelasan sudah jelas pada comment sc.
