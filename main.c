#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "todolist.h"
#include "myday.h"
#include "misc.h"


int main()
{
    printf("Welcome to Task management system 101\n");
    printf("Developed by Mohammad Owais Noor Butt\n");
    printf("----------------------------------\n");
    while(1){
        int selected_module = 0;

        //ask the user to select function/module from the main menu
        printf("1.To do list\n2.Create My day Schedule\n3.My Day\n");
        scanf("%d",&selected_module);


        //exiting code on 101
        if(selected_module == 101){
            printf("Exiting...");
            break;
        }
        //validation
        else if(selected_module!=1 && selected_module!=2 && selected_module!=3){
            printf("Please choose one of the options by inserting a number\n");
            break;
        }

        if(selected_module==1){
            todolist("todolist.txt");
        }
        else if(selected_module == 2){
            //get the time blocks(check if the pointer assignment works)
            //clear my day file
            FILE * myday = fopen("myday.txt","w");
            fclose(myday);

            int * time_blocks;
            time_blocks = create_time_blocks();
            if(time_blocks==-1){
                break;
            }

            //get the task(check if the pointer assignment works)
            int * tasks_chosen;
            tasks_chosen = choose_tasks_myday("todolist.txt");
            if(tasks_chosen==-1){
                break;
            }

            //map TASKS CHOSEN to TIME BLOCKS
            map_tasks_to_time_blocks(time_blocks,tasks_chosen,"myday.txt","todolist.txt");
            printf("\nSuccessful\n");


        }
        else if(selected_module == 3){
            my_day("myday.txt");
        }
    }
    return 0;


}
