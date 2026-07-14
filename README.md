# LexerWithAutomat

`LexerWithAutomat`, küçük bir eğitim dili için yazılmış masaüstü bir lexer çalışma alanıdır. Uygulama kaynak metni açma/düzenleme, lexical analiz çalıştırma, token listesini konum bilgileriyle gösterme ve çıktıyı temizleme/yazdırma işlevlerini sağlar.

Bu depo, 2012 tarihli öğrenci projesinin modern Qt 5 / Qt 6 araç zincirleri için güncellenmiş sürümünü içerir. Eski, kırılgan durum tablosu kodu; test edilebilir ve okunabilir bir lexer çekirdeğiyle değiştirilmiştir.

## Öne Çıkanlar

- Qt Widgets tabanlı sade masaüstü arayüz
- Ayrık `Lexer` sınıfı ile UI ve analiz mantığının ayrılması
- Satır ve sütun bilgisi içeren token çıktısı
- Geçersiz karakterler için açık hata raporlama
- Güvenli dosya kaydetme için `QSaveFile`
- Hem `qmake` hem `CMake` ile derleme desteği
- Qt Print Support ile yazdırma desteği

## Tanınan Token Türleri

- `TOKEN_BRACE_PAREN`: `(` `)` `{` `}`
- `TOKEN_PLUS_MINUS`: `+` `-`
- `TOKEN_ASSIGN_PLUS_MINUS`: `+=` `-=`
- `TOKEN_ASSIGN`: `=`
- `TOKEN_COMPARE`: `==`
- `TOKEN_RELATIONAL`: `<` `>`
- `TOKEN_SEPARATOR`: `;` `,`
- `TOKEN_INTEGER_LITERAL`
- `TOKEN_FLOAT_LITERAL`
- `TOKEN_IF`
- `TOKEN_WHILE`
- `TOKEN_INT`
- `TOKEN_IDENTIFIER`

## Proje Yapısı

- `main.cpp`: Uygulama giriş noktası
- `mainwindow.h` / `mainwindow.cpp`: Ana pencere, dosya işlemleri ve çıktı sunumu
- `lexer.h` / `lexer.cpp`: Lexer çekirdeği
- `mainwindow.ui`: Qt Designer arayüz tanımı
- `Res.qrc`: Uygulama ikon kaynakları
- `OmerNote.pro`: `qmake` projesi
- `CMakeLists.txt`: Modern CMake projesi

## Derleme

### Gereksinimler

- C++17 uyumlu bir derleyici
- Qt 5 veya Qt 6 geliştirme paketleri
  - Qt 5 için: `qtbase5-dev`
  - Qt 6 için: `qt6-base-dev`
- Yazdırma özelliği için Qt Print Support

### Ubuntu / Debian Paketleri

Qt 5 ile bu projeyi derlemek için aşağıdaki paketler yeterlidir:

```bash
sudo apt update
sudo apt install -y \
  build-essential \
  cmake \
  qtbase5-dev \
  qtbase5-dev-tools \
  qt5-qmake \
  qtchooser \
  libglu1-mesa-dev \
  libgl-dev \
  libegl-dev \
  libvulkan-dev \
  libxext-dev
```

### CMake ile

```bash
rm -rf build
cmake -S . -B build
cmake --build build -j"$(nproc)"
```

### qmake ile

```bash
rm -f Makefile
qmake OmerNote.pro
make -j"$(nproc)"
```

## Kullanım

1. Uygulamayı başlatın.
2. Kaynak kodu pencereye yapıştırın veya `Dosya > Aç` ile bir dosya yükleyin.
3. `Analiz > Lexical Analizi Çalıştır` komutunu verin.
4. Alt panelde token ve hata çıktılarını inceleyin.

Örnek giriş:

```txt
int counter = 10;
while (counter > 0) {
    counter -= 1;
}
```

## Lexer Kapsamı ve Sınırlar

Bu lexer, bilinçli olarak küçük bir token kümesini tanır. Aşağıdaki karakterler veya yapılar şu anda desteklenmez:

- Çift tırnak: `"`
- Tek tırnak: `'`
- Fonksiyon çağrısı için özel token kuralları
- String literal yapıları
- Karakter literal yapıları
- Bölme, çarpma, mod gibi operatörler: `/` `*` `%`
- Köşeli parantezler: `[` `]`
- İki nokta, yorum ve benzeri ek sözdizimleri

Örneğin aşağıdaki girişte `printf` bir `TOKEN_IDENTIFIER` olarak tanınır; ancak `"` karakteri lexer tarafından tanınmaz ve hata olarak raporlanır:

```txt
printf("test")
```

Bu örnekte beklenen davranış:

- `printf` tanınır
- `(` ve `)` tanınır
- `"` karakterleri tanınmaz
- `test` içeride harflerden oluştuğu için tanımlayıcı gibi ayrışır, fakat string literal olarak ele alınmaz

## Modernizasyon Notları

Bu güncellemede aşağıdaki teknik sorunlar giderildi:

- Qt 4 döneminden kalma `QtGui`/`trUtf8`/`toAscii` bağımlılıkları kaldırıldı
- Tanımsız davranış üreten tarama kodu kaldırıldı
- Dosya açtıktan sonra kaydetmenin yanlış hedefe yazabilmesi düzeltildi
- Lexer çıktısındaki taşma ve sonlandırma sorunları kaldırıldı
- Arayüz sabit koordinatlar yerine yeniden boyutlanabilir düzene geçirildi
- Derleme sistemi C++17 ve Qt Print Support ile güncellendi

## Not

Bu çalışma alanında Qt geliştirme başlıkları kurulu değilse yerel derleme doğrulaması yapılamaz. Proje dosyaları bu nedenle Qt 5 / Qt 6 geliştirme paketlerinin bulunduğu bir ortam hedeflenerek güncellenmiştir.
