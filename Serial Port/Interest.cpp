#include <iostream>
#include <vector>
#include <array>
#include <math.h>

using namespace std;


class Interest {
private:
    static unsigned int id;
    static const unsigned nr_fields = 5;
    array<array<bool,6>,nr_fields> fields; // consists of 1 set bit among 6 per field to represent interest from 0 to 5
    array<array<bool,25>,nr_fields> field_images; // the images associated to each field (25 bits each)
    array<unsigned,nr_fields> interest_values; // contains the interest values for each field as they keep getting updated in percentage 
public:

    Interest :: Interest (array<unsigned, nr_fields> &fields, array<array<bool,25>,nr_fields> &field_images) {

        for (unsigned i = 0; i < nr_fields; i++) {
            for (unsigned b = 0; b < 6; b++) {
                this->fields[i][b] = false;
            }
        }

        for (unsigned i = 0; i < nr_fields; i++) {
            for (unsigned b = 0; b < 6; b++) {
                this->field_images[i][b] = false;
            }
        }

        this->id++;

        for (unsigned i = 0; i < fields.size(); i++){
            for (unsigned v = 0; v < 6; v++) {
                if (fields[i] == v) {
                    this->fields[i][v] = true;
                    this->interest_values[i] = fields[i] * 20;
                    break;
                }
            }
        }

        for (unsigned i = 0; i < field_images.size(); i++) {
            for (unsigned b = 0; b < 25; b++) {
                if (field_images[i][b]) {
                    this->field_images[i][b] = true;
                }
            }
        }
    }
    unsigned int getID(){
        return this->id;
    }

    array<array<bool,6>,nr_fields> &getFields() {

        for (unsigned i = 0; i < nr_fields; i++) {
            for (unsigned b = 0; b < 6; b++) {
                this->fields[i][b] = false;
            }
        }
        
        for (unsigned i = 0; i < this->interest_values.size(); i++) {
            for (unsigned b = 0; b < 6; b++) {
                if (floor((interest_values[i] / 20)) == b) {
                    this->fields[i][b] = true;
                    break;
                }
            }
        }
        return this->fields;
    }

    array<bool,25> getImage(unsigned image_field) {
        return this->field_images[image_field];
    }

    void affect_Interest(array<array<bool,6>,nr_fields> &other_person_fields) {
        for (unsigned i = 0; i < other_person_fields.size(); i++) {
            for (unsigned b = 0; b < 6; b++) {
                if (other_person_fields[i][b]) {
                    if (other_person_fields[i][b] - this->interest_values[i] >= 40) {
                        this->interest_values[i] += 10 + 5 * floor(abs(other_person_fields[i][b] - this->interest_values[i] - 40)) / 20;
                    }
                    else if (this->interest_values[i] - other_person_fields[i][b] >= 40) {
                        this->interest_values[i] -= 10 + 5 * floor(abs(other_person_fields[i][b] - this->interest_values[i] - 40)) / 20;
                    }
                }
            }
        }
    }

    unsigned get_Max(array<unsigned,3> &array) {
        unsigned max = 0;
        for (int i = 1; i < 3; i++) {
            if (array[i] > array[max]) {
                max = i;
            }
        }
        return max;
    }

    array<unsigned,nr_fields> &sort_by_Max_Interest(array<unsigned,nr_fields> &interest_values) {
        array<unsigned,nr_fields> sorted_fields; //instead of unsigned, 3 bits can be used
        for (unsigned nr_remaining_fields = nr_fields; nr_remaining_fields > 0; nr_remaining_fields--) {
            unsigned max_interest = 0;
            for (unsigned i = 1; i < nr_remaining_fields; i++) {
                bool ignore_this_field = false;
                for (int n = 0; n < sorted_fields.size(); n++) {
                    if (i == sorted_fields[n]) {
                        ignore_this_field = true;
                        break;
                    }
                }
                if (ignore_this_field) {
                    continue;
                }
                if (interest_values[i] > interest_values[max_interest]) {
                    max_interest = i;
                }
            }
            sorted_fields[nr_fields-nr_remaining_fields] = max_interest;
        }
        return sorted_fields;
    }

    array<bool,25> &get_Image_To_Flash(array<array<array<bool,6>,nr_fields>,10> &other_ppl_fields) {
        array<unsigned,this->nr_fields> sorted_fields = sort_by_Max_Interest(interest_values);
        array<unsigned,3> field_popularity; // only has the 3 fields everyone's more interested in
        for (unsigned i = 0; i < this->nr_fields; i++) { // initialize popularity at 0
            field_popularity[i] = 0;
        }
        for (unsigned i = 0; i < 3; i++) {
            for (unsigned p = 0; p < 10; p++) { // for every person

                if (other_ppl_fields[p][sorted_fields[i]][5] == true) {
                    field_popularity[sorted_fields[i]]+= 3;
                }
                else if (other_ppl_fields[p][sorted_fields[i]][4] == true) {
                    field_popularity[sorted_fields[i]]+= 2;
                }
                else if (other_ppl_fields[p][sorted_fields[i]][3] == true) {
                    field_popularity[sorted_fields[i]]++;
                }
            }
        }
        return this->field_images[get_Max(field_popularity)];
    }
};

unsigned int Interest :: id{0};