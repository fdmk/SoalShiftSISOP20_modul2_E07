# SoalShiftSISOP20_modul2_E07
Soal 1

![1_1](https://user-images.githubusercontent.com/61625353/77227389-9a949180-6bb2-11ea-8b9d-4d2c4aacb58f.PNG)

Fungsi di atas merupakan fungsi cekangka dan cekbintang untuk mengecek apakah input berupa angka atau bintang.

![2_1](https://user-images.githubusercontent.com/61625353/77227480-3d4d1000-6bb3-11ea-8407-55541f4698b0.PNG)

Fungsi cekpath untuk mengecek apakah path file yang di inputkan valid

![l](https://user-images.githubusercontent.com/61625353/77227564-c6644700-6bb3-11ea-8ec1-c904adba61ad.PNG)

Mengecek apakah argumen yang dimasukkan berjumlah 5, jika tidak maka akan diberikan pesan error

![pegel karo ledis](https://user-images.githubusercontent.com/61625353/77227632-4d192400-6bb4-11ea-9886-50f9f1f38540.PNG)

Mengecek apakah input yang dimasukkan sesuai dengan yang diminta, jika tidak sesuai akan dikeluarkan pesan error.

![ngakuo](https://user-images.githubusercontent.com/61625353/77227694-b1d47e80-6bb4-11ea-91e3-27124c0bb476.PNG)

Mengubah nilai string menjadi integer

Mengecek apakah input sesuai range detik menit jam

Mengecek apakah file path sesuai

![taim](https://user-images.githubusercontent.com/61625353/77227781-4808a480-6bb5-11ea-9ceb-2de857becad9.PNG)

Memasukkan detik, menit, jam ke tm dan memasukkan kondisi input yang valid
Menjalankan execv

Soal 2

A. Dalam poin ini kita diminta untuk membuat directory setiap 30 detik dengan nama waaktu pembuatan directori. Langkah pertama kita membuat char sebagai penyimpan nama directory dengan format waktu, langkah kedua kita mengambil time stamp [YYYY-MM-DD_hh:ii:ss] menggunakan “struct time_t” kemudian dimasukkan kedalam char tersebut.

B. Dalam poin ini kita diminta melakukan unduhan 20 gambar dari link https://picsum.photos/   
setiap 5 detik dengan ukuran (unix time%1000)+100,Langkah pertama kita membuat char sebagai penyimpan current time untuk nama dari gambar yang di unduh, langkah kedua melakukan unduhan  serta pemberian nama pada file yang diunduh, langkah ketiga memberi ukuran pada foto dalam langkah ini kita mengambil unix time menggunakan “struct time_t”

C. Dalam poin ini kita me-commpress directory hasil unduhan kita, setelah berhasil kita menghapus directory tersebut

P.S. untuk ketereangan lebih lanjut terdapat pada comment SC
