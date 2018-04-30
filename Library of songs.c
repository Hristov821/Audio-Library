#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct SongList
    {
        char *SongLocation;
        char *ArtistName;
        char *Title;
        char *AlbumTitle;
        int Year;
        char *Genre;
        double Rating;
        struct SongList *Next;
    };
/// shte zapisvam samo dyljinata na masiva bez terminirashtata 0
    struct SongList *Head=NULL;
    char *Audio_Library="Audio_Library.bin";
    void insertAtList(struct SongList *Temp);
    int IsDataEmpty(char *Audio_Library);
    void ReadFromData();
    void ReWriteBinFILE(char *Audio_Library);
    void ALLprintList();
    int isStringsEqual(char * st,char * nd);
    int delateAllSongsFromGivenArtist(char *searchArtistName);
    int  printDublingSongs(struct SongList *curr,struct SongList *temp);
    void DifStructures();

    void DeleteListFromMemory();
int main()
{
    //ALLprintList();

    int IsFileEmpty=IsDataEmpty(Audio_Library);
    if(IsFileEmpty)
    {
        printf("\t \t \t No Data in Library \n");
    }
    else
    {
        ReadFromData();
    }

    int Choice=1;
  // ALLprintList();
        while(Choice!=4)
        {
            printf(" For Inserting New Song Press 1 \n");
            printf(" For Printing All Dubling Songs Press 2 \n");
            printf(" For Delating All Songs From Given Artist Press 3 \n");
            printf(" For Exit Press 4 \n");
            printf(" Type a choice = ");
            scanf("%d",&Choice);
            if(Choice==1)
            {
            printf("case 1 \n");
            fflush(stdin);
            struct SongList *ptr=(struct SongList*)malloc(sizeof(struct SongList));
            ptr->SongLocation=(char *)calloc(100,1);
            ptr->ArtistName=(char *)calloc(100,1);
            ptr->AlbumTitle=(char *)calloc(100,1);
            ptr->Title=(char *)calloc(100,1);
            ptr->Genre=(char *)calloc(100,1);

            printf(" Song location :");
            fgets(ptr->SongLocation,99,stdin);
            printf("Artist name :");
            fgets(ptr->ArtistName,99,stdin);
            printf("Title :");
            fgets(ptr->Title,99,stdin);
            printf("Album Title :");
            fgets(ptr->AlbumTitle,99,stdin);
            printf("Genre :");
            fgets(ptr->Genre,99,stdin);
            printf("Year and Rating:");
            scanf("%d %lf:",&ptr->Year,&ptr->Rating);
            fflush(stdin);


            insertAtList(ptr);
            free(ptr->SongLocation);
            free(ptr->ArtistName);
            free(ptr->AlbumTitle);
            free(ptr->Title);
            free(ptr->Genre);
            free(ptr);
            //ALLprintList();
            ReWriteBinFILE(Audio_Library);
            fflush(stdin);
            }
            /// CASE 2
            if(Choice==2)
            {
                if(Head!=NULL)
                {
                    printf("case 2 \n");
                    DifStructures();
                    ReWriteBinFILE(Audio_Library);
                    fflush(stdin);
                }
                else{
                    printf(" \n list is empty \n");
                }

            }
            /// CASE 3
          if(Choice==3)
            {
            printf("case 3\n Artist name = ");
            fflush(stdin);
            char Aname[100];
            fgets(Aname,99,stdin);
            int temp=delateAllSongsFromGivenArtist(Aname);
            while(temp!=0)
            {
                temp=delateAllSongsFromGivenArtist(Aname);
            }
            ReWriteBinFILE(Audio_Library);
            }
            /// CASE 4
        }
           if(Choice==4)
            {
            printf("case 4 \n");
            ReWriteBinFILE(Audio_Library);
            DeleteListFromMemory();
            fflush(stdin);
            }


    return 0;
}
void insertAtList(struct SongList *Temp)
{
    struct SongList *NewSong=(struct SongList*)malloc(sizeof(struct SongList));

    NewSong->SongLocation=(char *)calloc(strlen(Temp->SongLocation)+1,1);
     strcpy(NewSong->SongLocation,Temp->SongLocation);
    NewSong->ArtistName=(char *)calloc(strlen(Temp->ArtistName)+1,1);
     strcpy(NewSong->ArtistName,Temp->ArtistName);
    NewSong->Title=(char *)calloc(strlen(Temp->Title)+1,1);
     strcpy(NewSong->Title,Temp->Title);
    NewSong->AlbumTitle=(char *)calloc(strlen(Temp->AlbumTitle)+1,1);
     strcpy(NewSong->AlbumTitle,Temp->AlbumTitle);
    NewSong->Year=Temp->Year;
    NewSong->Genre=(char *)calloc(strlen(Temp->Genre)+1,1);
     strcpy(NewSong->Genre,Temp->Genre);
    NewSong->Rating=Temp->Rating;

    NewSong->Next=NULL;
    if(Head==NULL)
    {
        Head=NewSong;
        return;
    }
    struct SongList *FindLast=Head;
    while(FindLast->Next!=NULL)
    {
        FindLast=FindLast->Next;
    }
    FindLast->Next=NewSong;
}
    void ReadFromData()
    {
       FILE *fp;
        int SongLocation;
        int ArtistName;
        int Title;
        int AlbumTitle;
        int Genre;
        struct SongList *Song=(struct SongList *)malloc(sizeof(struct SongList));
        if((fp=fopen(Audio_Library,"rb"))!=0)
        {
            // POMISLI POSLE ZA FUNKCIQ TUK
            while(1)
            {

                if((fread(&SongLocation,sizeof(int),1,fp))==0)
                {
                    break;
                }
                Song->SongLocation=(char*)malloc(SongLocation+1);
                fread(Song->SongLocation,SongLocation,1,fp);
                Song->SongLocation[SongLocation]='\0';

                fread(&ArtistName,sizeof(int),1,fp);
                Song->ArtistName=(char *)malloc(ArtistName+1);
                fread(Song->ArtistName,ArtistName,1,fp);
                Song->ArtistName[ArtistName]='\0';

                fread(&Title,sizeof(int),1,fp);
                Song->Title=(char*)malloc(Title+1);
                fread(Song->Title,Title,1,fp);
                Song->Title[Title]='\0';
                fread(&AlbumTitle,sizeof(int),1,fp);
                Song->AlbumTitle=(char*)malloc(AlbumTitle+1);
                fread(Song->AlbumTitle,AlbumTitle,1,fp);
                Song->AlbumTitle[AlbumTitle]='\0';

                fread(&Song->Year,sizeof(int),1,fp);

                fread(&Genre,sizeof(int),1,fp);
                Song->Genre=(char *)malloc(Genre+1);
                fread(Song->Genre,Genre,1,fp);
                Song->Genre[Genre]='\0';

                fread(&Song->Rating,sizeof(double),1,fp);

                insertAtList(Song);
            }
            free(Song);
           fclose(fp);
           // gornite redove trqbva da gi naprawq na funkciq
        }
    }
int IsDataEmpty(char *Audio_Library)
{
    int filestatment;
    FILE *fp;
    if((fp=fopen(Audio_Library,"rb"))==0)
    {
        filestatment= 1;
    }
    else
    {
        long savedOffset = ftell(fp);
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
        {
        filestatment= 1;
        }
        fseek(fp, savedOffset, SEEK_SET);
        filestatment= 0;
    }
    fclose(fp);
    return filestatment;
}
 void ReWriteBinFILE(char *Audio_Library)
 {
     FILE *fp;
     if((fp=fopen(Audio_Library,"wb"))!=0)
        {
            struct SongList *curr=Head;
            while(curr!=NULL)
                {

                        int lenSongLocation;
                        int lenArtistName;
                        int lenofTitle;
                        int lenofAlbumTitle;
                        int lenOofGenre;

                        lenSongLocation=strlen(curr->SongLocation);
                        lenArtistName=strlen(curr->ArtistName);
                        lenofTitle=strlen(curr->Title);
                        lenofAlbumTitle=strlen(curr->AlbumTitle);
                        lenOofGenre=strlen(curr->Genre);

                        fwrite(&lenSongLocation,sizeof(int),1,fp);
                        fwrite(curr->SongLocation,lenSongLocation,1,fp);

                        fwrite(&lenArtistName,sizeof(int),1,fp);
                        fwrite(curr->ArtistName,lenArtistName,1,fp);

                        fwrite(&lenofTitle,sizeof(int),1,fp);
                        fwrite(curr->Title,lenofAlbumTitle,1,fp);

                        fwrite(&lenofAlbumTitle,sizeof(int),1,fp);
                        fwrite(curr->AlbumTitle,lenofAlbumTitle,1,fp);

                        fwrite(&curr->Year,sizeof(int),1,fp);

                        fwrite(&lenOofGenre,sizeof(int),1,fp);
                        fwrite(curr->Genre,lenOofGenre,1,fp);

                        fwrite(&curr->Rating,sizeof(double),1,fp);
                    curr=curr->Next;
                }
        }
        fclose(fp);
 }

 void ALLprintList()
 {
     struct SongList *curr=Head;
     while(curr!=NULL)
     {
         printf("%s \n",curr->SongLocation);
         printf("%s \n",curr->ArtistName);
         printf("%s \n",curr->Title);
         printf("%s \n",curr->AlbumTitle);
         printf("%s \n",curr->Genre);
         printf("%d \n",curr->Year);
         printf("%lf \n",curr->Rating);
         curr=curr->Next;
     }
 }
////////////////
int isStringsEqual(char * st,char * nd)
{
    char *first=(char *)malloc(strlen(st)+1);
    strcpy(first,st);
    const char del[1] = " ";
    int numberofnames=1;
    int count =0;
    char **ptrToNames1=(char **)malloc(sizeof(char*)* numberofnames);
    char *token=strtok(first,del);
    while(token!=NULL)
    {
        if(count==numberofnames)
        {
            ptrToNames1=(char **)realloc(ptrToNames1,sizeof(char*)*numberofnames*2);
            numberofnames*=2;
        }
        ptrToNames1[count]=(char*)malloc(strlen(token)+1);
        strcpy(ptrToNames1[count],token);
        count++;
        token=strtok(NULL,del);
    }
   //// za 2ra duma nadolu
    char *second=(char*)malloc(strlen(nd)+1);
    strcpy(second,nd);
    int numberofnames2=1;
    int count2=0;
     char **ptrToNames2=(char **)malloc(sizeof(char*)* numberofnames2);
     token=strtok(second,del);
     while(token!=NULL)
     {
         if(count2==numberofnames2)
         {
             ptrToNames2=(char **)realloc(ptrToNames2,sizeof(char*)*numberofnames2*2);
            numberofnames2*=2;
         }
        ptrToNames2[count2]=(char*)malloc(strlen(token)+1);
        strcpy(ptrToNames2[count2],token);
        count2++;
        token=strtok(NULL,del);
     }
     int Coincidences=0;
     int mismatches=0;
    if(count==count2)
    {
        int i;
        for(i=0;i<count;i++)
        {
            if( !strcmp(ptrToNames2[i],ptrToNames1[i]))
            {
                Coincidences++;
            }
            else
            {
                 mismatches++;
            }
        }
    }
    //// free
    int i;
    for(i=0;i<count;i++)
    {
        free(ptrToNames1[i]);
    }
    for(i=0;i<count2;i++)
    {
        free(ptrToNames2[i]);
    }
    free(ptrToNames1[i]);
    free(ptrToNames2);
    //// end free
    if(Coincidences>=mismatches)
    {
        return 1;
    }
    return 0;
}
 int delateAllSongsFromGivenArtist(char *searchArtistName)
 {
     if(Head==NULL)
     {
         return 0;
     }
     struct SongList *curr=Head;
     struct SongList *prev=NULL;
     while(curr!=NULL&& (!isStringsEqual(curr->ArtistName,searchArtistName)))
     {

         prev=curr;
         curr=curr->Next;
     }
     if(prev==NULL)
     {
         Head=curr->Next;
         free(curr->AlbumTitle);
         free(curr->ArtistName);
         free(curr->Genre);
         free(curr->SongLocation);
         free(curr->Title);
         free(curr);
         return 1;
     }
    else if(curr==NULL)
     {
         return 0;
     }
     else
     {
         prev->Next=curr->Next;
         free(curr->AlbumTitle);
         free(curr->ArtistName);
         free(curr->Genre);
         free(curr->SongLocation);
         free(curr->Title);
         free(curr);
         return 1;
     }
 }
 int printDublingSongs(struct SongList *curr,struct SongList *temp)
 {
     if(isStringsEqual(curr->ArtistName,temp->ArtistName))
     {
         //printf("vliza 1 if");
         if((!strcmp(curr->AlbumTitle,temp->AlbumTitle))&&(!strcmp(curr->Title,temp->Title))
             &&(!strcmp(curr->Genre,temp->Genre))&&(curr->Year==temp->Year))
            {
            printf(" \n Artist Name %s   %s \n",curr->ArtistName,temp->ArtistName);
            printf("\n Album Title %s %s \n ",curr->AlbumTitle,temp->AlbumTitle);
            printf("\n ");
            return 1;
            }
     }
     return 0;
 }
void DifStructures()
{
    struct SongList * curr=Head;
    struct SongList *ToHead=Head->Next;
    while(curr->Next!=NULL)
    {
            while(ToHead!=NULL)
            {
                int a;
                a=printDublingSongs(ToHead,curr);
                printf("%d",a);
                ToHead=ToHead->Next;
            }
        curr=curr->Next;
        ToHead=curr->Next;
    }
}


  void DeleteListFromMemory()
  {
      struct SongList * curr=Head;
      struct SongList *next;
      while(curr!=NULL)
      {
          free(curr->SongLocation);
          free(curr->ArtistName);
          free(curr->Title);
          free(curr->AlbumTitle);
          free(curr->Genre);
          next=curr->Next;
          free(curr);
          curr=next;
      }
    Head=NULL;
  }
