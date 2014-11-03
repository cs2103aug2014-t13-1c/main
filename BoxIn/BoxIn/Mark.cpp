#include "Mark.h"


Mark::Mark(std::string input){
    name = parser.getField(input, TypeName);
    field = FIELD_DONE;
    newValue = ""; // placeholder. Doesn't really matter since will just mark  as opposite
}


Mark::~Mark(void){
}
