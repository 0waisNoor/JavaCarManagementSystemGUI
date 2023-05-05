int * create_time_blocks(){
    static int time_blocks[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char *time_intervals[24] = {"6:00 - 7:00","7:00 - 8:00","8:00 - 9:00","9:00 - 10:00","10:00 - 11:00","11:00 - 12:00","12:00 - 13:00","13:00 - 14:00","14:00 - 15:00","15:00 - 16:00","16:00 - 17:00","17:00 - 18:00","18:00 - 19:00","19:00 - 20:00","20:00 - 21:00","21:00 - 22:00","22:00 - 23:00","23:00 - 24:00","24:00 - 1:00","1:00 - 2:00","2:00 - 3:00","3:00 - 4:00","4:00 - 5:00","5:00 - 6:00"};


    while(1){
        int time_block_index;
        char RW;

        //display time blocks
        printf("\Step 1. Time blocks in a day\n");
        for (int i=0;i<24;i++){
        if(time_blocks[i]==0){
            printf("%d %s %s \n",i+1,time_intervals[i],"Rest");
        }else{
            printf("%d %s %s \n",i+1,time_intervals[i],"Work");
            }
        }
        //ask user to select time block by entering time block position
        printf("Select time block (press 101 when you are done): \n");
        scanf("%d",&time_block_index);


        //exit the loop instance, this means the user has selected all time blocks
        if(time_block_index == 101){
            break;
        }

        //validate the input
        if(time_block_index<0 || time_block_index>24){
            printf("Error:Invalid input\n");
            return -1;
        }

        //ask the user whether the time block entered is rest or work and store the as RW
        printf("Is the time rest or work? R/W\n");
        scanf(" %c",&RW);

        //edit index to value 0 if it is Rest and 1 if it is Work
        if(RW =='R' | RW == 'r'){
                time_blocks[time_block_index-1]=0;
        }
        else if(RW =='W' | RW == 'w'){
                time_blocks[time_block_index-1]=1;
        }
        else{
            printf("Invalid input\n");
        }

    }

    //this part of the code will display the finalized time blocks in proper format
    //and also
    //calculate the work hours by finding the number of 1s in TIME BLOCKS ARRAY
    int work_hours_count = 0;
    for(int i=0;i<24;i++){
        if(time_blocks[i]==0){
            printf("%d %s %s \n",i+1,time_intervals[i],"Rest");
        }else{
            printf("%d %s %s \n",i+1,time_intervals[i],"Work");
            //WORKHOURS = number of 1s in time block array as each time block represents one hour
            work_hours_count++;
        }
    }
    printf("Your workhours for the day: %d hours\n",work_hours_count);

    return time_blocks;
}


int * choose_tasks_myday(char file_url[20]){

    //stores the task positions in the todolist which the user wants to include in "my day" section
    //MY DAY TASK POSITIONS should be initilized to array of 0 which represents a null value
    static int my_day_task_pos[20] = { 0 };

    //display to do list
    printf("\nTO DO list\n");
    int num_tasks = display_tasks(file_url);

    //LOOP TO GET MULTIPLE task positions (allows a maximum of 20 tasks)
	printf("Step2. Choose task(101 to exit)\n");
    for(int i=0;i<20;i++){
        //ask user to enter task and store it
        scanf("%d",&my_day_task_pos[i]);

        //exit
        if(my_day_task_pos[i]==101){
            //remove the value from the array as it is an exit command
            my_day_task_pos[i]=0;
            break;
        }

        //validation
        if(my_day_task_pos[i]<=0 || my_day_task_pos[i]>num_tasks){
            printf("Error:invalid task ");
            return -1;
        }
    }
    return my_day_task_pos;
}


void display_work_time_blocks(int *time_block_array, char *time_intervals[24]){
     //display TIME BLOCKS for work and their durations with proper formatting
     printf("Time blocks:\n");
     int pos=0;
     for(int i=0;i<24;i++){
        if(time_block_array[i]==1){
            printf("%d. %s\n",++pos,time_intervals[i]);
        }
     }
}


void map_tasks_to_time_blocks(int *time_block_array,int *tasks_positions,char *mydayurl,char *todolisturl){
     char *time_intervals[24] = {"6:00-7:00","7:00-8:00","8:00-9:00","9:00-10:00","10:00-11:00","11:00-12:00","12:00-13:00","13:00-14:00","14:00-15:00","15:00-16:00","16:00-17:00","17:00-18:00","18:00-19:00","19:00-20:00","20:00-21:00","21:00-22:00","22:00-23:00","23:00-24:00","24:00-1:00","1:00-2:00","2:00-3:00","3:00-4:00","4:00-5:00","5:00-6:00"};

    printf("\nStep 3. Assign tasks to each work time block\n\n");
     //display TIME BLOCKS for work and their durations with proper formatting
     printf("Time blocks:\n");
     int pos=0;
     for(int i=0;i<24;i++){
        if(time_block_array[i]==1){
            printf("%d. %s\n",++pos,time_intervals[i]);
        }
     }


     //values being 0 which represent null
     char my_day_tasks[20][200] = {0};
     //this is incremented every time something is added to above array
     //in order to append future values
     int my_day_tasks_last_index = 0;

     //extract only the tasks that have positions in TASKS POSITION ARRAY in parameter
     FILE *file = fopen(todolisturl,"r");
     char task[100];

     for(int i=0;fgets(task,100,file)!=NULL;i++){
        for(int j=0;j<20;j++){
            if(i == tasks_positions[j] && tasks_positions[j] != 0){
                //append task to MY DAY TASKS ARRAY
                strcpy(my_day_tasks[my_day_tasks_last_index],task);
                my_day_tasks_last_index++;

                //this task position has been extracted so change value to null to prevent comparison in next loop instance
                tasks_positions[j]=0;

            }
        }
     }
     fclose(file);

     //display MY DAY TASKS ARRAY
     printf("Tasks for today:\n");
     for(int i=0;i<20;i++){
        if(strcmp(my_day_tasks[i],"")!=0){
                printf("%d. %s",i+1,my_day_tasks[i]);
        }

     }

    FILE *myday = fopen(mydayurl,"a");
     //LOOP through TIME BLOCKS for work(1s only and not 0s) one by one
     //this will assign tasks to each time block
     for(int i=0;i<24;i++){
        if(time_block_array[i]==1){

            int tasks_to_include_indexes[20]={0};
            //this is incremented every time something is added to above array
            //in order to append future values
            int tasks_to_incl_last_index = 0;


            //LOOP until length of selected tasks is acceptable
            int satisfactory_duration=0;
            while(satisfactory_duration==0){

                printf("\nEnter tasks to allocate to time block %s (type 101 to when done)\n",time_intervals[i]);

                //validate the data

                //this loop will keep asking user for tasks positions until tasks duration are <=60
                while(1){
                     scanf(" %d",&tasks_to_include_indexes[tasks_to_incl_last_index++]);
                    //we subtract 1 from index as the it has been incremented and therefore refers to next value currently
                     if(tasks_to_include_indexes[tasks_to_incl_last_index-1]==101){
                        tasks_to_include_indexes[tasks_to_incl_last_index-1]=0;
                        break;
                     }
                }

                //these two variables will be used to calculate the duration
                //of tasks that have their index stored in TASKS TO INCLUDE INDEXES ARRAY
                int task_durations[20] = {0};
                int task_durations_index=0;
                int durations_sum = 0;

                //this array stores extra values from sscanf below and will be disposed
                char temp[4] = {0};

                //loop through MY DAY TASKS ARRAY and extract chosen tasks, chosen tasks are in TASKS TO INCLUDE ARRAY
                for(int i=0;i<20;i++){

                    //if tasks_to_include_indexes[i] is 0, it means null
                    if(tasks_to_include_indexes[i]==0){
                        break;
                    }
                    //extract durations from TASKS TO INCLUDE
                    sscanf(my_day_tasks[tasks_to_include_indexes[i]-1],"%s %d %s %s %s",&temp[0],&task_durations[task_durations_index++],&temp[1],&temp[2],&temp[3]);
                }


                //ensure that durations of task chosen does not exceed 1hr
                for(int i=0;i<20;i++){
                    durations_sum +=task_durations[i];
                }
                if(durations_sum>60){

                    //change TASKS TO INCLUDE to blank array again so we can reuse it
                    for (int i=0;i<20;i++){
                        tasks_to_include_indexes[i] = 0;
                    }
                    tasks_to_incl_last_index = 0;

                    printf("Your tasks for this time block must be a maximum of 1 hour\n");
                    //this repeats the commands for selecting user tasks again
                }else{

                    //break the loop
                    satisfactory_duration=1;
                }

            }

            for(int y=0;y<20;y++){
                //0 means that the array value is blank
                if(tasks_to_include_indexes[y]==0){
                    continue;
                }
             fprintf(myday,"%s %s %s",time_intervals[i],"0%",my_day_tasks[tasks_to_include_indexes[y]-1]);
            }

            //LOOP through TASKS TO INCLUDE ARRAY and write it to MY DAY FILE in the format time interval, task

        }
     }
    fclose(myday);
}


int update_myday_task_progress(char file_url[50],int line_pos, int progress_value){
    const int attribute_pos = 1; //this is the position for progress field
    char row[200];
    FILE *file = fopen(file_url,"r+");
    FILE *temp = fopen("temp.txt","w+");

    for(int i=0;!feof(file);i++){
        //reads current line
        fgets(row,200,file);
        if(i==line_pos){
            char line_to_edit[7][20];
            sscanf(row,"%s %s %s %s %s %s %s",line_to_edit[0],line_to_edit[1],line_to_edit[2],line_to_edit[3],line_to_edit[4],line_to_edit[5],line_to_edit[6]);
            //line_to_edit now contains value of required row as array values

            //update the attribute in the array
            char progress_value_string[4];
            itoa(progress_value,progress_value_string,10);
            strcat(progress_value_string,"%");
            strcpy(line_to_edit[attribute_pos],progress_value_string);
            //print the new row to the temp file
            fprintf(temp,"%s %s %s %s %s %s %s\n",line_to_edit[0],line_to_edit[1],line_to_edit[2],line_to_edit[3],line_to_edit[4],line_to_edit[5],line_to_edit[6]);

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

    //replace contents of file with contents of temp file
    remove(file_url);
    rename("temp.txt",file_url);
}


int delete_myday_task(char file_url[50],int line_pos){
    char row[200];
    FILE *file = fopen(file_url,"r");
    FILE *temp = fopen("temp.txt","w+");

    for(int i=0;!feof(file);i++){

        //reads current line
        fgets(row,200,file);
        if(i==line_pos){
            continue;
        }else{
            //break code at the end to avoid printing last line twice
            if (feof(file)){
                break;
            }
            fprintf(temp,"%s",row);
        }
    }
    //remove the todolist file and rename temp.txt to todolist.txt
    fclose(file);
    fclose(temp);

    //rename temp.txt to todolist.txt
    remove(file_url);
	rename("temp.txt",file_url);
    return 0;
}


int my_day(char myday_file_url[20]){
    printf("\nMy day tasks\n");
    int num_tasks = display_tasks(myday_file_url);

    //ask user to select task
    printf("Which task do you want to select\n");
    int task_pos;
    scanf("%d",&task_pos);

    //validate task_pos - must be a +integer and should exist
    if(task_pos<=0){
        printf("Error: Invalid task position\n");
        return -1;
    }
    else if(task_pos>num_tasks){
        printf("Error:Task position does not exist\n");
        return -1;
    }

    //ask user for the progress of selected task
    printf("Enter progress of task\n");
    int progress;
    scanf("%d",&progress);

    //validate
    if(progress>100 ||  progress<0){
        printf("Progress must be a value between 0 and 100\n");
        return -1;
    }

    if(progress!=100){
        update_myday_task_progress(myday_file_url,task_pos,progress);
    }else{
    //if it is task is 100% then remove it
        delete_myday_task(myday_file_url,task_pos);

    }
    printf("Successful\n");
    return 0;
}
