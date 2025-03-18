#include <iostream>
#include <cstdlib>
#include <ctime>
#include "coordinate.h"
void add_coordinate(Coordinate *&list_end, float x, float y)
{

	Coordinate *coord = (Coordinate*)malloc(sizeof(Coordinate));	
	if (coord== nullptr)	
	{
		std::cout<< "Error failed memory alloction"<< std:: endl;
		return;
	}


	coord->x = x;	
	coord->y = y;
	coord->next = nullptr;
	coord->previous = list_end;
	
	if (list_end)
        {
	
		coord->coord_id = list_end->coord_id + 1;
		list_end->next = coord;
	}  
	
	else  
	{
        	coord->coord_id = 1;
   	}

	list_end = coord;
}


void forward_display(Coordinate *list_beginning)
{	
	Coordinate *list = list_beginning;

	while(list)
	{
		std::cout<<"Coordnates ID:  " <<list->coord_id << std::endl;
		std::cout<<"x and y coordinate: " << std::endl;
		std::cout<<"x: " << list->x << "   y: "<< list->y << std::endl;
	
	list = list->next;
	}
}

void backward_display(Coordinate *list_end)
{
   	Coordinate *list = list_end;

    	while (list)
   	{
        	std::cout << "Coordinate ID: " << list->coord_id << std::endl;
        	std::cout << "x and y coordinates: " << std::endl;
        	std::cout << "x: " << list->x << "   y: " << list->y << std::endl;

        	list = list->previous;
	}
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
   
    Coordinate *list = list_beginning;

    while (list)
    {
        if (list->coord_id == coord_id_to_delete)  
        {
           
		if (list->previous)
		{
			list->previous->next = list->next;
		}
            
		if (list->next)
                {	
			list->next->previous = list->previous;
		}
		
            std::cout << "Deleting coordinate ID: " << list->coord_id << "\n";
            free(list);
            return;
        }

        list = list->next;
    }

    std::cout << "Coordinate ID " << coord_id_to_delete << " not found." << std::endl;
}

int list_length(Coordinate *list_beginning)
{
	int count = 0;
	Coordinate *list = list_beginning;

	while (list)
	{
        	count++;
        	list = list->next;
	}

	return count;
}







int main(int argc, char *argv[])



{
	if (argc !=2)
	{
		printf("error to many commands: %d\n",argc);
		printf("only two allowed:\n");
	
	return 0;
	}
		
	int pairs = std::stoi(argv[1]);
	srand(time(nullptr));

    	Coordinate *first = nullptr;
    	Coordinate *last = nullptr;

    	for (int i = 0; i < pairs; i++)
    	{
        	float x = (rand() % 1000) / 10.0f;
        	float y = (rand() % 1000) / 10.0f;
        if (!first)  
        {
            first = (Coordinate*)malloc(sizeof(Coordinate));
            if (!first) 
            {
                std::cerr << "Memory allocation failed.\n";
                return 1;
            }

            	first->x = x;
            	first->y = y;
            	first->coord_id = 1;
            	first->next = first->previous = nullptr;
           	 last = first;
        }
        else
        {
            add_coordinate(last, x, y); 
        }
    }

	

    	std::cout << "\nDisplaying coordinates forward:\n";
    	forward_display(first);

    	std::cout << "\nDisplaying coordinates backward:\n";
    	backward_display(last);

	std::cout << "\nDeleting coordinate ID 5...\n";
    	delete_coordinate(first, 5);
	
	Coordinate *temp = first;
	
	last = first;
	while (last && last->next)
	{
    		last = last->next;
	}

	std::cout << "\nUpdated coordinate list:\n";
    	forward_display(first);
	
	while (first)
	{
    		Coordinate *temp = first;
    		first = first->next;
    		free(temp);
	}
}      	                           
