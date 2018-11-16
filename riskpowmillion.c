//Terrence Light
//11/6/2015
//COP 3502 University of Central Florida
//Risk^1,000,000 Battle Simulator

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b);
void QuickSort(int* nums, int start, int end);
int partition(int* nums, int start, int end);
void bubble(int* atk, int* def, int* used, int wins, int high);

int main(){
    //Read in number of test cases
    int numCases, i;
    scanf("%d", &numCases);

    //Run based on the number of cases
    for(i = 0; i < numCases; i++){

        //Read in the troop data
        int battles, j;
        scanf("%d", &battles);

        //Create arrays to store the attacker and defender data
        int* attacker = malloc(sizeof(int)*battles);
        int* defender = malloc(sizeof(int)*battles);

        //Store attacker and defender data
        for(j = 0; j < battles; j++){
            scanf("%d", &attacker[j]);
        }

        for(j = 0; j < battles; j++){
            scanf("%d", &defender[j]);
        }

        //Sort the array
        QuickSort(attacker, 0, battles-1);
        QuickSort(defender, 0, battles-1);

        //Counter to track defender wins
        int wins = 0;

        //Testing solutions now. Try used array
        int* atkUsed = calloc(battles, sizeof(int));

        /**To optimally position the defensive soldiers we must match each defensive army strength
        as close to a tie with the attackers while still winning**/
        //Use a method somewhat similar to a bubble movement
        bubble(attacker, defender, atkUsed, wins, battles-1);

        //Free memory
        free(atkUsed);
        free(attacker);
        free(defender);
    }
}

void QuickSort(int* nums, int start, int end){
    //If we have more than 1 element to sort
    if (start <= end){

        //First partition the array of numbers
        int part = partition(nums, start, end);

        //Recursively quick sort the left and right sides
        QuickSort(nums, start, part-1);
        QuickSort(nums, part+1, end);
    }
}

void swap(int *a, int *b){
    //Swap two items
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* nums, int start, int end){
    //Base case, only sort if there is something to be sorted
    if(start == end){
        return start;
    }

    //We must first partition the array
    //Pick random starting value
    int randPart = start + rand()%(end-start+1);

    //Keep track of the original start value
    int initialStart = start;

    //Swap the partition and the start
    swap(&nums[start], &nums[randPart]);

    //Update start so that the partition isn't part of sort
    start++;

    //Start sorting
    //Partition should only go while start doesn't cross end
    while(start <= end){

        //First move the start pointer until a value is larger than the partition
        while(start <= end && nums[start] < nums[initialStart]){
            start++;
        }

        //Then move the end pointer until a value is smaller or equal to the partition
        while(end >= start && nums[end] >= nums[initialStart]){
            end--;
        }

        //Swap the numbers to the correct side of the array
        if(start < end){
            swap(&nums[start], &nums[end]);
        }
    }

    //Swap partition back in place
    swap(&nums[initialStart], &nums[end]);

    //Return partition element
    return end;

}

void bubble(int* atk, int* def, int* used, int wins, int high){
    int i, j, k;

    //Used array won't need track high end of array
    //We never go out of order for defender array, so need to make used array for it

    //Use a for loop to go through
    //j will track the lowest non-used value on attacker side
    for(i = 0, j = 0; i < high+1; i++){

        //Sometimes values in the middle of the array become used, we'll need to
        //skip them as we come across them
        while(used[j] == 1){
            j++;
        }

        //If the current slot isn't used
        if(!used[j]){

            //If in the sorted array atk and def are = for this battle, def wins
            if(def[i] == atk[j]){
                wins++;
                used[j] = 1;
                j++;
                continue;
            }

            //If the lowest defender value is less than the lowest attacker value
            //Then decrement the high value since it is now matched with the lowest defender battle
            //in a loss
            if(def[i] < atk[j]){
                used[high] = 1;
                continue;
            }

            //Try to find the highest value this defending army can beat
            int add = 0;

            //Will be used to mark the last usable attacker army to win against
            int mark;

            //j value is already checked to be unused earlier in the program and
            //add starts at 0, so it's safe to store that are the mark
            //def[i] guaranteed to be > atk[j] by the past checks

            mark = j + add;

            while(def[i] >= atk[j+add]){

                if(!used[j+add]){
                    mark = j + add;

                    //If the next attacker army would beat the current defending army
                    //But the current attacking army doesn't, use the current for a win
                    if(def[i] < atk[j+add] && !used[j+add]){
                        wins++;
                        used[j+add] = 1;
                        break;
                    }

                    //If not, go to the next attacking army
                    add++;

                }

                else{
                    add++;
                }

                wins++;
                used[mark] = 1;
                break;
            }

            //Reset add
            add = 0;
        }
    }

    //Print out number of defending wins
    printf("%d\n", wins);

}
