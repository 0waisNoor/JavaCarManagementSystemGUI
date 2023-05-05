int compare_dates(char date1[10],char date2[10]){
    int yr1,yr2,mnth1,mnth2,day1,day2;
    sscanf(date1,"%d/%d/%d",&day1,&mnth1,&yr1);
    sscanf(date2,"%d/%d/%d",&day2,&mnth2,&yr2);

    //checking year
    if(yr1>yr2){
        return 1;
    }else if(yr1<yr2){
        return -1;
    }else if(yr1 == yr2){
        //checking month
        if(mnth1>mnth2){
            return 1;
        }else if(mnth1<mnth2){
            return -1;
        }else if(mnth1 == mnth2){
            //checking day
            if(day1>day2){
                return 1;
            }else if(day1<day2){
                return -1;
            }else if(day1 == day2){
                return 0;
            }
        }
    }
}


// Function to perform Selection Sort
void selectionSort(char arr[50][5][30], int n,int attr_pos,int asc)
{

    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++){
            if(asc==1){
                if (strcmp(arr[j][attr_pos],arr[min_idx][attr_pos])<0){
                    min_idx = j;
                }
            }else if(asc==0){
                if (strcmp(arr[j][attr_pos],arr[min_idx][attr_pos])>0){
                    min_idx = j;
                }
            }

        }


        // Swap the found minimum element
        // with the first element
        char temp[5][30];
        for(int k=0;k<5;k++){
            strcpy(temp[k],arr[i][k]);
        }
        for(int k=0;k<5;k++){
            strcpy(arr[i][k],arr[min_idx][k]);
        }
        for(int k=0;k<5;k++){
            strcpy(arr[min_idx][k],temp[k]);
        }

    }

    //print tasks
    for(int a=0;a<50;a++){
        if(strcmp(arr[a],"")==0){
            continue;
        }
        for(int b=0;b<5;b++){
            printf("%s ",arr[a][b]);
        }
        printf("\n");
    }
}


void selectionSortDate(char arr[50][5][30], int n,int attr_pos,int asc)
{

    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++){
            if(asc==1){
                if (compare_dates(arr[j][attr_pos],arr[min_idx][attr_pos])<0){
                    min_idx = j;
                }
            }else if(asc==0){
                if (compare_dates(arr[j][attr_pos],arr[min_idx][attr_pos])>0){
                    min_idx = j;
                }
            }

        }


        // Swap the found minimum element
        // with the first element
        char temp[5][30];
        for(int k=0;k<5;k++){
            strcpy(temp[k],arr[i][k]);
        }
        for(int k=0;k<5;k++){
            strcpy(arr[i][k],arr[min_idx][k]);
        }
        for(int k=0;k<5;k++){
            strcpy(arr[min_idx][k],temp[k]);
        }

    }

    //print tasks
    for(int a=0;a<50;a++){
        if(strcmp(arr[a],"")==0){
            continue;
        }
        for(int b=0;b<5;b++){
            printf("%s ",arr[a][b]);
        }
        printf("\n");
    }
}


int validate_date(char time_string[8]){
    //this function validates time entered

    int day;
    int month;
    int year;
    sscanf(time_string,"%d/%d/%d",&day,&month,&year);

    if(year<=2022 && year>=2122){
        printf("Invalid year\n");
        return -1;
    }
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        if(!(day>0 && day<=31)){
            printf("invalid day\n");
            return -1;
        }
    }else if (month == 4 || month == 6 || month == 9 || month == 11){
        if(!(day>0 && day<=30)){
            printf("invalid day\n");
            return -1;
        }
    }else if(month==2){
        //check for leap year
        if(year%4==0){
                if(!(day>0 && day<=28)){
                    printf("invalid day\n");
                    return -1;
                }
        }else{
            if(!(day>0 && day<=29)){
                printf("invalid day\n");
                return -1;
                }
        }

    }else{
        printf("invalid month\n");
        return -1;
    }

    return 0;

}


int validate_duration(char value[30]){


    if(strcmp(value,"0")!=0 && strcmp(value,"15")!=0 && strcmp(value,"30")!=0 && strcmp(value,"45")!=0 && strcmp(value,"60")!=0){
        return -1;
    }

    return 0;
}
