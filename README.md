Да се разработи програма с меню тип файлова аудио библиотека: . Информацията за аудио файловете се съхраняват в двоични файлове. За всеки файл се пазят следните данни:
 Име/път на файл.
 Изпълнител 
 Заглавие 
 Албум 
 Година 
 Жанр 
 Рейтинг (от 0 до 5). 
Да се извършват следните обработки:
 а) добавяне на нова песен в базата данни;

 б) Извеждане на всички двойки дублиращи се песни. Намирането на дубликати да стане, като се сравняват гореспоменатите данни за песен (без името на файла и рейтинг) дали са сходни, като годината трябва да е същата.
    За сходни низове, се приема ако двата низа имат повече еднакви думи отколкото различни. Пример: File: File1.mp3 File2.mp3  File3.mp3 File4.mp3 Artist:  Guns 'n' Roses Guns and Roses Guns 'n' Roses Groove Coverage Title:  Paradise         City Paradise City Poison Poison 
    Анализ: File1 и File2 се дублират, тъй като изпълнителя има 2 съвпадащи думи: “Guns” и “Roses”, както и  File2 и File3 не се дублират, тъй като заглавието е различно.
    File3 и File4  не се дублират тъй като изпълнителя е различен.
    
 г) Изтриване на данните за всички песни от даден изпълнител.
 
 Данните да се поддържат в динамична структура - едносвързан списък в оперативната памет на ПК
