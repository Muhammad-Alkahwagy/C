/*************************************************/
/* Description: Clinic management system with C  */
/* Date       : 24-Mar-2023                      */
/* Author     : Muhammad Sameer Alkahwagy        */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

typedef struct PatientNode
{
    int id;
    int age;
    char name[MAX_SIZE];
    char gender[8];
    char slot[7];

    struct PatientNode* next;
}patient;

typedef struct PatientsList
{
    patient* head;
    int size;
}patients;

typedef struct SlotNode
{
    char data[7];
    struct SlotNode* next;
}slot;

typedef struct SlotList
{
    slot* head;
    int size;
}slots;


char* Def_Slots[5] = {"2:00PM","2:30PM","3:00PM","4:00PM","4:30PM"};
char initial[]= "None";
int res_count =0;


/*Functions prototypes*/
void List_voidInit(patients* pl);
int List_intIsEmpty(patients* pl);
int List_intGetSize(patients* pl);

void SList_voidInit(slots* psl);
int SList_intIsEmpty(slots* psl);
int SList_intGetSize(slots* psl);
void SList_voidInsertLast(slots* psl, char* Copy_charValue);
void SList_voidInsertSlot(slots* psl,char* Copy_charValue, int pos);
void SList_voidDeleteList(slots* psl, int pos);
void SList_voidDeleteSlot(slots* psl,char* Copy_charValue);
void SList_voidPrint(slots* psl);

int Check_ID(patients* pl, int ID);
int Check_SLot(char* Slot, slots* psl);
void Reserve_Slot(patients* pl, slots* psl ,int ID, char* Slot);
void Cancel_Reservation(patients* pl, slots* psl,int ID);

void Add_Patient(patients* pl, char* Name, char* Gender, int Age, int ID);
void Edit_Record(patients* pl, char* Name, char* Gender, int Age, int ID);
void View_Record(patients* pl, int ID);
void View_Reservations(patients* pl);

int main()
{   
    int input, password, Age;
    char Name[MAX_SIZE];
    char Gender[8];
    char Slot[7];

    int ID;
    int* pID = &ID;

    patients l1;  //patients list
    patients* pl1 = &l1;

    slots l2; //slots list
    slots* psl1 = &l2;

    List_voidInit(pl1);
    SList_voidInit(psl1);

    for(int i =0; i<5; i++)
        SList_voidInsertLast(psl1,Def_Slots[i]);

    printf("\n\n*******************************************************\n");
    printf("\n************** Clinic Management System ***************\n");
    printf("\n*******************************************************\n");
    while(1)
    {
        printf("\n(1)Admin (2)User  (3) Exit\n");
        printf("Choice: ");
        scanf("%d",&input);
        switch(input)
        {
            case 1: //Admin Mode
                printf("\nPlease enter password: ");
                scanf("%d",&password);
    
                for(int i=0;i<2;i++)
                {
                    if(password != 1234)
                    {
                        printf("\nTry again: ");
                        scanf("%d",&password);
                    }
                }
                if(password==1234)
                {
                    while(1)
                    {
                        printf("\n******************** Admin mode ********************");
                        printf("\n(1)Add new patient (2)Edit a patient's record");
                        printf("\n(3)Reserve a slot  (4)Cancel reservation\t(5)Go back->\n");
                        fflush(stdin);
                        printf("Choice: ");
                        scanf("%d",&input);
                        if(input == 5)
                            break;
                        switch (input)
                        {
                            case 1: //add patient
                                printf("\nEnter patient's information!\n");
                                printf("ID: "); 
                                fflush(stdin);
                                scanf("%d",&ID);
                                if(Check_ID(pl1,ID)) //ID doesn't exist
                                {   
                                    fflush(stdin);
                                    printf("Name: ");
                                    scanf("%[^\n]s",Name);
                                    printf("Gender: ");
                                    fflush(stdin);
                                    scanf("%[^\n]s",Gender);
                                    printf("Age: ");
                                    scanf("%d",&Age);

                                    Add_Patient(pl1,Name,Gender,Age,ID);
                                    printf("\nRecord is added successfully!!\n");
                                }
                                else
                                    printf("\nID already exists!!\n");
                                break;
                            case 2: //edit record
                                printf("\nEnter patient's ID: "); 
                                scanf("%d",&ID);
                                if(!Check_ID(pl1,ID)) //ID exists
                                {   
                                    fflush(stdin);
                                    printf("*Name: ");
                                    scanf("%[^\n]s",Name);
                                    printf("*Gender: ");
                                    fflush(stdin);
                                    scanf("%[^\n]s",Gender);
                                    printf("*Age: ");
                                    scanf("%d",&Age);
                                    Edit_Record(pl1,Name,Gender,Age,ID);
                                    printf("\nRecord is edited successfully!!\n");
                                }
                                else
                                    printf("\nNon-existing ID!!\n");
                                break;
                            case 3: //reserve a slot
                                printf("\nAvailable slots: ");
                                SList_voidPrint(psl1);
                                printf("\nEnter patient's ID: "); 
                                scanf("%d",&ID);
                                if(!Check_ID(pl1,ID)) //ID exists
                                {   
                                    fflush(stdin);
                                    printf("Desired slot: ");
                                    scanf("%[^\n]s",Slot);
                                    if(Check_SLot(Slot,psl1)) //slot is available
                                    {
                                        Reserve_Slot(pl1,psl1,ID,Slot);
                                        printf("\nReservation successfull!\n");
                                    }
                                    else
                                        printf("\nUnavailable slot!\n");
                                }
                                else
                                    printf("\nNon-existing ID!!\n");
                                break;
                            case 4: //cancel reservation
                                printf("\nEnter patient's ID: "); 
                                scanf("%d",&ID);
                                if(!Check_ID(pl1,ID)) //ID exists
                                {   
                                    Cancel_Reservation(pl1,psl1,ID);
                                    printf("\nReservation is canceled successfully!!\n");
                                }
                                else
                                    printf("\nNon-existing ID!!\n");
                                break;
                            default:
                                break;
                        }

                    }
                }
                else
                {
                    printf("\nIncorrect password for 3 times! Access denied!\n");
                    return 1;
                }

                break;

            case 2: //user mode
                while(1)
                {
                    printf("\n\n#################### User mode ####################");
                    printf("\n(1)View patient's record\n(2)View today's reservations\n(3)Go back->\n");
                    printf("Choice: ");
                    scanf("%d",&input);
                    if(input == 3)
                        break;
                    switch (input)
                    {
                        case 1: //view record
                            printf("\nEnter patient's ID: "); 
                            scanf("%d",&ID);
                            if(!Check_ID(pl1,ID))
                            {
                                printf("\nPatient #%d",ID);
                                View_Record(pl1,ID);
                            }
                            else
                                printf("\nNon-existing ID!!\n");
                            break;
        
                        case 2: //view reservations
                            printf("\nToday's reservations:\n");
                            View_Reservations(pl1);
                            break;
        
                        default:
                            break;
                    }
                }
                break;

            case 3:
                printf("\n********************** Goodbye **********************\n");
                return 1;
    
            default:
                printf("\nInvalid choice!\n");
                break;
                
        }

    }

    return 0;
}


/**********************************Functions definitions****************************************************************/

int Check_ID(patients* pl, int ID)
{
    patient *tmp = pl->head;
    while(tmp)
    {
        if(tmp->id == ID) //checking for existing ID
            return 0;
        else
            tmp = tmp->next;
    }     
    return 1;
}

void Add_Patient(patients* pl, char* Name, char* Gender, int Age, int ID)
{   
    patient* pn = (patient*)malloc(sizeof(patient));

    strcpy(pn->name,Name);
    strcpy(pn->gender,Gender);
    strcpy(pn->slot,initial);
    pn->age = Age;
    pn->id = ID;
    pn->next = NULL;
    
    if(List_intIsEmpty(pl))
        pl->head = pn;
    else
    {
        patient* tmp = pl->head;
        while(tmp->next)
            tmp = tmp->next;

        tmp->next = pn;
    }
    pl->size++;

}

void Edit_Record(patients* pl, char* Name, char* Gender, int Age, int ID)
{
    patient *tmp = pl->head;
    while(tmp)
    {
        if(tmp->id == ID) //looking for existing ID
        {
            strcpy(tmp->name,Name);
            strcpy(tmp->gender,Gender);
            tmp->age = Age;
            tmp->id = ID;

            break;
        }
        else
            tmp = tmp->next;
    }    
}

void View_Record(patients* pl, int ID)
{
    patient *tmp = pl->head;
    while(tmp)
    {
        if(tmp->id == ID) //checking for existing ID
        {
            printf("\nName: %s",tmp->name);
            printf("\nGender: %s",tmp->gender);
            printf("\nAge: %d",tmp->age);
            printf("\nReservation: %s",tmp->slot);

            printf("\n");
            break;
        }
        else
            tmp = tmp->next;
    }     
}

int Check_SLot(char* Slot, slots* psl)
{   
    slot *tmp = psl->head;
    while(tmp)
    {
        if (!strcmpi(tmp->data , Slot)) //checking is slot is available
            return 1;
        else
            tmp = tmp->next;
    }     
    return 0;
}

void Reserve_Slot(patients* pl, slots* psl ,int ID, char* Slot)
{   
    patient *tmp = pl->head;
    while(tmp)
    {
        if(tmp->id == ID) //looking for existing ID
        {
            strcpy(tmp->slot,Slot);
            res_count++;
            SList_voidDeleteSlot(psl,Slot);
            break;
        }
        else
            tmp = tmp->next;
    }    

}

void View_Reservations(patients* pl)
{   
    patient *tmp = pl->head;

    if(res_count)
    {   
        int i = 0;
        while(tmp)
        {   
            if(strcmpi(tmp->slot,initial))
            {
                printf("\n%s : Patient #%d",tmp->slot,tmp->id);      
                i++;
            }
            tmp = tmp->next;
            
            if(i==res_count)
                break;
        }     
        free(tmp);
    }
    else
        printf("None!");
}

void Cancel_Reservation(patients* pl, slots* psl,int ID)
{
    //set slot to initial
    patient *tmp = pl->head;
    
    while(tmp)
    {
        if(tmp->id == ID) //looking for existing ID
        {
            for(int i=0; i<5; i++)
            {
                if(!strcmpi(tmp->slot,Def_Slots[i]))
                    SList_voidInsertSlot(psl,tmp->slot,i); //make slot available again
            }

            strcpy(tmp->slot,initial);
            res_count--;
            break;
        }
        else
            tmp = tmp->next;
    }    
}

void List_voidInit(patients* pl)
{
    pl->head = NULL;
    pl->size = 0;
}

int List_intIsEmpty(patients* pl)
{
    return (pl->head == NULL);
}

//Slots list functions
void SList_voidInit(slots* psl)
{
    psl->head = NULL;
    psl->size = 0;
}

int SList_intIsEmpty(slots* psl)
{
    return (psl->head == NULL);
}

int SList_intGetSize(slots* psl)
{
    return psl->size;
}

void SList_voidInsertLast(slots* psl, char* Copy_charValue)
{
    slot* pn = (slot*)malloc(sizeof(slot));
    strcpy(pn->data,Copy_charValue);
    pn->next = NULL;

    if(SList_intIsEmpty(psl))
        psl->head = pn;
    else
    {
        slot* tmp = psl->head;
        while(tmp->next)
            tmp = tmp->next;

        tmp->next=pn;
    }
    
    psl->size++;
}

void SList_voidInsertSlot(slots* psl,char* Copy_charValue, int pos) //generic case
{
    slot* pn = (slot*)malloc(sizeof(slot));
    strcpy(pn->data,Copy_charValue);
    
    slot* tmp = psl->head;
    for(int i=0;i<pos-1;i++)
        tmp = tmp->next;

    pn->next = tmp->next;
    tmp->next = pn;
    psl->size++;
}

void SList_voidPrint(slots* psl)
{   
    if(!SList_intIsEmpty(psl))
    {
        slot *tmp = psl->head;

        while(tmp)
        {
            printf(" %s",tmp->data);
            tmp = tmp->next;
        }     
        free(tmp);
        putchar('\n');
    }
    else
        printf("empty!\n");
}

void SList_voidDeleteSlot(slots* psl,char* Copy_charValue)
{   
        //loop in the list checking for value
        slot *tmp = psl->head;

        int pos =0;
        while(tmp)
        {
            if(!strcmpi(tmp->data,Copy_charValue))
            {
                tmp = tmp->next;
                SList_voidDeleteList(psl,pos);
            }
            else
                tmp = tmp->next;
            
            pos++;
        }     
        free(tmp);
}

void SList_voidDeleteList(slots* psl, int pos)
{   
        if(pos==0) //pos==0
        {
            psl->head = psl->head->next;
        }
        else
        {
            slot* tmp1 = psl->head;
            for(int i=0;i<pos-1;i++)
                tmp1 = tmp1->next;
    
            slot* tmp2 = psl->head;
            for(int i=0;i<pos;i++)
                tmp2 = tmp2->next;
    
            tmp1->next = tmp2->next;
            free(tmp2);
        }
        psl->size--;
}