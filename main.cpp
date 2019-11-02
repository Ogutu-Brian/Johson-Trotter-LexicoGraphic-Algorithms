#include<iostream>
#include <vector>

using namespace std;

const string LEFT = "LEFT";
const string RIGHT = "RIGH";

struct Element{
    char value;
    string direction;
    bool is_mobile;
};

void print_directions(vector<Element> directed_integers){
    cout<<"\t";

    for(Element element: directed_integers){
        if(element.direction == LEFT){
            cout<<"<-";
        }else{
            cout<<"->";
        }
    }

    cout<<endl;
}

void print_elements(vector<Element> directed_integers){
    cout<<"\t";

    for(Element element: directed_integers){
        cout<<element.value<<" ";
    }

    cout<<endl;
}

void print_permutation(vector<Element> directed_integers){
    print_directions(directed_integers);
    print_elements(directed_integers);
}

bool mobile(Element element, Element neighbour){
    return element.value > neighbour.value;
}

bool is_mobile(vector<Element> directed_integers, int index){
    if(directed_integers.size() == 1){
        return false;
    }

    Element element = directed_integers[index];

    if((index == 0 && element.direction == LEFT) || (index == directed_integers.size() - 1 && element.direction == RIGHT)){
        return false;
    }

    if(element.direction == LEFT){
        Element neighbour = directed_integers[index - 1];

        return mobile(element, neighbour);
    }else{
        Element &neighbour = directed_integers[index + 1];

        return mobile(element,neighbour);
    }
}

void assign_mobile_properties(vector<Element> &directed_integers){
    int index = 0;

    for(Element &element: directed_integers){
        element.is_mobile = is_mobile(directed_integers,index);
        index++;
    }
}

void swap_elements(Element &element, Element &neighbour){
    char temp_value = element.value;
    string temp_direction = element.direction;

    element.value = neighbour.value;
    element.direction = neighbour.direction;
    neighbour.value = temp_value;
    neighbour.direction = temp_direction;
}


void switch_permutation_directions(vector<Element> &directed_integers, Element current_element){
    for(Element &element: directed_integers){
        if(element.value > current_element.value){
           if(element.direction == LEFT){
               element.direction = RIGHT;
           }else{
               element.direction = LEFT;
           }
        }
    }
}

vector<int> get_mobile_indices(vector<Element> directed_integers){
    vector<int> indices;

    for(int i = 0; i < directed_integers.size(); i++){
        if(directed_integers[i].is_mobile){
            indices.push_back(i);
        }
    }

    return  indices;
}

int get_largest_index(vector<int> indices,vector<Element> directed_integers){
    int largest_index = indices[0];
    Element largest_element = directed_integers[indices[0]];

    for(int i = 1; i < indices.size(); i++){
        if(largest_element.value < directed_integers[indices[i]].value){
            largest_index = indices[i];
            largest_element.value = directed_integers[indices[i]].value;
        }
    }

    return largest_index;
}

void johnson_trotter(string input_string){
    vector<Element> directed_integers;
    vector<int> mobile_indices;

    for(char c:input_string){
        Element element;
        element.value = c;
        element.direction = LEFT;
        element.is_mobile = true;

        directed_integers.push_back(element);
    }

    cout <<"1: ";
    print_permutation(directed_integers);
    mobile_indices = get_mobile_indices(directed_integers);

    int count = 2;

    while(mobile_indices.size() > 0){
        cout<<count<<": ";
        int largest_mobile_index = get_largest_index(mobile_indices,directed_integers);

        Element largest_ement = directed_integers[largest_mobile_index];

        if(directed_integers[largest_mobile_index].direction == LEFT && largest_mobile_index != 0){
            swap_elements(directed_integers[largest_mobile_index],directed_integers[largest_mobile_index - 1]);
        }else{
            if(largest_mobile_index != directed_integers.size() - 1){
               swap_elements(directed_integers[largest_mobile_index],directed_integers[largest_mobile_index + 1]);
            }
        }

        switch_permutation_directions(directed_integers,largest_ement);

        cout<<"\n";
        print_permutation(directed_integers);

        assign_mobile_properties(directed_integers);
        mobile_indices= get_mobile_indices(directed_integers);

        count++;
    }
}


//void lexicographic_permute(string input_string){
//   for(char &c: input)
//}

int main(){
    //    string input_string;

    //    cout<<"Enter a string: ";
    //    cin>>input_string;
    //    cout<<std::endl;

    cout<<"JOHNSON TROTTER ALGORITHM"<<endl;
    johnson_trotter("1234");
    cout<<"\n";

//    cout<<"LEXICOGRAPHIC ALGORITHM"<<endl;
//    lexicographic_permute("1234");
}
