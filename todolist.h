
char * generate_date(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    static char time_string[10];
    sprintf(time_string,"%02d/%02d/%d", tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);

    return time_string;
}

void add_task(char file_url[50],char user_input[5][30]){
    //raw string is from user in format: add task1 15 19/09/2022 idb
    FILE *file = fopen(file_url,"a");
    //we start from user_input[1] since the first word is the command keyword 'add'
    char *date = NULL;
    date = generate_date();

    //validate the date entered by user
    if (validate_date(user_input[3])==-1){
        return -1;
    }

    fprintf(file,"%s %s %s %s %s\n",user_input[1],user_input[2],user_input[3],user_input[4],date);
    fclose(file);
}


int display_tasks(char file_url[20]){
    FILE *file = fopen(file_url,"r");
    char contents[200];
    int num_lines = 0;
    for(int c=0;fgets(contents,200,file);c++){
        //first line of file is always blank
        printf("%d. %s",c,contents);
        printf("\n");

       num_lines++;
    }
    fclose(file);
    //codeblocks compiler automatically inserts blank line after last line in file
    num_lines--;
    return num_lines;
}



int update_task(char file_url[50],int line_pos){
    int attribute_pos;
    char row[200],new_value[20];
    FILE *file = fopen(file_url,"r");
    FILE *temp = fopen("temp.txt","w+");

    printf("Which attribute do you want to update?\n1.Task description\n2.Duration \n3.Due date\n4.Category\n");
    scanf("%d",&attribute_pos);

    //exit
    if(attribute_pos==101){
        return -1;
    }

	//validate option selected
	if(attribute_pos!=1 && attribute_pos!=2 &&  attribute_pos!=3 && attribute_pos!=4){
		printf("Error: Invalid option\n");
		return -1;
	}


    printf("What is the new value?\n");
    scanf("%s",new_value);

    //attribute pos will be used as index which starts from 0 so subtract 1
    attribute_pos--;
	//validation
	//for duration
	if(attribute_pos==1){
		if(validate_duration(new_value)==-1){
            printf("this is the one being taken\n");
			return -1;
		}
	}
	//for due date
	if(attribute_pos==2){
        if(validate_date(new_value)==-1){
            return -1;
        }
	}

    for(int i=0;!feof(file);i++){

        //reads current line
        fgets(row,200,file);
        if(i==line_pos){
            char line_to_edit[5][30];
            sscanf(row,"%s %s %s %s %s",line_to_edit[0],line_to_edit[1],line_to_edit[2],line_to_edit[3],line_to_edit[4]);
            //line_to_edit now contains value of required row as array values

            //update the attribute in the array
            strcpy(line_to_edit[attribute_pos],new_value);
            //print the new row to the temp file
            fprintf(temp,"%s %s %s %s %s\n",line_to_edit[0],line_to_edit[1],line_to_edit[2],line_to_edit[3],line_to_edit[4]);

        }else{

            //break code at the end to avoid printing last line twice
            if (feof(file)){
                 break;
            }

             //normally print it without editing if its not the required line
            fprintf(temp,"%s",row);
        }
    }
    fclose(file);
    fclose(temp);


        //rename temp.txt to todolist.txt
    remove(file_url);
    rename("temp.txt",file_url);

    return 0;
}


void delete_task(int line_position,char file_url[20]){
    FILE *file = fopen(file_url,"r");
    FILE *temp = fopen("temp.txt","w+");
    char row[200];
    //user input in the format "del line_position"
    for(int i=0;!feof(file);i++){
        fgets(row,200,file);

        //as soon as it reaches the line position, it skips it
        if(i==line_position){
            continue;
        }
         //the two lines of code below prevent the last line from printing twice
        if (feof(file)){
            break;
        }

        fputs(row,temp);
       }

	fclose(file);
	fclose(temp);

    //rename temp.txt to todolist.txt
    remove("todolist.txt");
    rename("temp.txt","todolist.txt");
}


void todolist(char todolist_file_url[20]){
    //this function will be called when option 1 is selected in the main menu
    FILE* todolist = fopen(todolist_file_url,"r");
    char c = fgetc(todolist);//if file is blank, check='\n'
    c = fgetc(todolist);//if file is blank, check='\n'
    fclose(todolist);

    //if the contents of todolist are blank then print an acceptable message
    if (c=='\n'){
        printf("[Blank file: please add some tasks]\n");
    }

    //display contents of the file and get the number of tasks
    printf("\nYour TO DO list:\n");
    printf("Task Format: description duration due_date category date_created \n");
    int num_tasks = display_tasks("todolist.txt");

    //get commands from user
    fflush(stdin);
    char command[100];
    fgets(command,100,stdin);
    char command_kword[4] = {command[0],command[1],command[2],'\0'};

    //ADD COMMAND
    if(strcmp(command_kword,"add")==0){
        //break command down to words
        char words[6][30];
        sscanf(command, "%s %s %s %s %s %s",words[0],words[1],words[2],words[3],words[4],words[5]);

        //VALIDATIONS:
        //validate duration
        if(strcmp(words[2],"0")!=0 && strcmp(words[2],"15")!=0 && strcmp(words[2],"30")!=0 && strcmp(words[2],"45")!=0 && strcmp(words[2],"60")!=0){
            printf("Error: Task duration can only be 0,15,30,45 or 60 minutes\n");
        }else{
            //this is the function that adds the task
            add_task("todolist.txt",words);
        }

    }

    //DEL COMMAND
        if(strcmp(command_kword,"del")==0){
        //break command down to words
        char words[2][30];
        sscanf(command, "%s %s",words[0],words[1]);

        //VALIDATIONS:
        int line_to_del = atoi(words[1]);
        //ensure input to del command is positive
        if(line_to_del<=0){
            printf("Error: Invalid task position\n");
        }
        //ensure that input to del is a line number
        else if(line_to_del>num_tasks){
            printf("Error:Task position does not exist\n");
        }
        else{
            //this is the function that adds the task
            delete_task(line_to_del,todolist_file_url);
        }

    }

    //UPD COMMAND
    if(strcmp(command_kword,"upd")==0){
        //break command down to words
        char words[2][30];
        sscanf(command, "%s %s",words[0],words[1]);

        //VALIDATIONS:
        int line_to_update = atoi(words[1]);
        //ensure input to del command is positive
        if(line_to_update<=0){
            printf("Error: Invalid task position\n");
        }
        //ensure that input to del is a line number
        else if(line_to_update>num_tasks){
            printf("Error:Task position does not exist\n");
        }
        else{
            //this is the function that adds the task
            update_task("todolist.txt",line_to_update);
        }
    }
    if(strcmp(command_kword,"srt")==0){
        sort_list("todolist.txt");
    }

}


void sort_list(file_url){

    //get tasks and number of tasks
    char row[200];
    FILE *file = fopen(file_url,"r");
    char tasks[50][5][30] = {0};
    int i;
    for(i=0;!feof(file);i++){
        fgets(row,200,file);
        if(strcmp(row,"")==0 || i==0){
            continue;
        }
        sscanf(row,"%s %s %s %s %s",tasks[i-1][0],tasks[i-1][1],tasks[i-1][2],tasks[i-1][3],tasks[i-1][4]);
        //prevent the last line from being read twice
        if (feof(file)){
                 break;
            }
    }
    fclose(file);
    int num_tasks = i;

    printf("Sort by:\n1.Task description\n2.Duration\n3.Due date\n4.Category\n5.Date created\n");
    int user_input=0;
    scanf("%d",&user_input);

    //validation
    if(user_input<0 || user_input >5){
            printf("Error:invalid input\n");
        return -1;
    }

    printf("What order? Ascending=1;Descending=0;\n");
    int asc;
    scanf("%d",&asc);
    //validation
    if(asc!=0 && asc!=1){
        printf("Error:invalid input\n");
        return -1;
    }

    printf("\n");
    if(user_input==1 || user_input==2 || user_input==4){
        //selectionSort(tasks,num_tasks,user_input-1,asc);
        selectionSort(tasks,num_tasks,user_input-1,asc);
    }else if(user_input==3 || user_input==5){
        selectionSortDate(tasks,num_tasks,user_input-1,asc);
    }
    printf("\n");
}

