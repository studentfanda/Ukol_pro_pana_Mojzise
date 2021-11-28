#include<bits/stdc++.h>

void valid_handler(std::string line, std::ofstream* output, std::string* first_value, std::string* last_value) {
    int comma_index=line.find(',');
    std::string first_arg=line.substr(0, comma_index);
    if(*first_value == "NaN")
        *first_value=first_arg;
    *last_value=first_arg;
    int arg;
    try {
        arg = std::stoi(first_arg);
    }
    catch(...){
        arg=-1;
    }
    if(arg%2==0){
        *output << ++arg << line.substr(comma_index) << std::endl;
    }
}

void invalid_handler(std::string line, int number, std::ofstream* log) {
    time_t now;
    time(&now);
    char buf[sizeof "2021-24-11T14:01:07"];
    strftime(buf, sizeof buf, "%FT%T", gmtime(&now));

    *log << buf << "," << number << ",[" << line << "]" << std::endl;

}

void line_handler(std::string line, int line_number, int attr_cnt, std::ofstream* output, std::ofstream* log, int* valid_lines_count, int* invalid_lines_count, std::string* first_value, std::string* last_value) {
    if(count(line.begin(),line.end(),',')!=attr_cnt-1){
        *invalid_lines_count = *invalid_lines_count+1;
        invalid_handler(line, line_number, log);
    }
    else{
        *valid_lines_count=*valid_lines_count+1;
        valid_handler(line, output, first_value, last_value);
    }
}

int main() {
    //I will record the time to start processing, if the program ends prematurely with an error, then I will not write the time
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream config_file( "test.conf" );
    std::string line;
    bool default_values=false;
    // In this step we can set default values in params and just update some values read from the file.
    // But in the assignment there was only the possibility of the non-existence of the configuration file, not its bad or incomplete format.
    std::map<std::string, std::string> params = {};
    // If the file could not be opened, load the default values
    if(config_file.fail()){
        default_values=true;
        params={
                {"log_file","default.log"},
                {"input_file","input.default"},
                {"output_file","output.default"},
                {"attr_cnt","2"}
        };
    }
        // Otherwise, I go through all the lines of the configuration file and take the part before the first '=' as a key and the rest as a value
    else {
        while (std::getline(config_file, line)) {
            int separator_index = line.find('=');
            std::string key = line.substr(0, separator_index);
            std::string value = line.substr(separator_index + 1);
            params[key] = value;
        }
    }
    // End of configuration loading
    config_file.close();

    // I'm opening the log file
    std::ofstream log(params["log_file"], std::ios::app);
    // If the opening fails, I will print an error on the console, but I will write the other errors to the log
    if(log.fail()){
        std::cout << "failed to open log file";
    }

    // number of attributes
    int attr_cnt;
    try{
        attr_cnt=std::stoi(params["attr_cnt"]);
    }
    catch(std::invalid_argument){
        log << "invalid number of arguments";
        return 1;
    }
        // I do not expect this variant to happen, but still
    catch(std::out_of_range){
        log << "the number of attributes is out_of_range";
        return 1;
    }

    std::ifstream input_file(params["input_file"]);
    if(input_file.fail()){
        log << "input file failed to open, probably does not exist";
        return 1;
    }
    std::ofstream output_file(params["output_file"]);
    if(output_file.fail()){
        log << "output file failed to open, probably does not exist";
        return 1;
    }
    // I am preparing variables that I will rewrite during processing
    // I assume that the number of lines will fit in the integer
    int line_number=0;
    int valid_lines_count=0;
    int invalid_lines_count=0;
    std::string first_value= "NaN";
    std::string last_value= "NaN";

    while (std::getline(input_file, line)){
        line_number++;
        line_handler(line, line_number, attr_cnt, &output_file, &log, &valid_lines_count, &invalid_lines_count, &first_value, &last_value);
    }

    if(line_number==0){
        log << "The input file was empty. There is nothing to process";
    }
    log << "valid lines: " << valid_lines_count << std::endl;
    log << "invalid lines: " << invalid_lines_count << std::endl;
    log << "first argument of the first line: " << first_value <<std::endl;
    log << "first argument of the last line: " << last_value <<std::endl;
    if(default_values){
        log << "the program used default values" << std::endl;
        for (const auto& [key, value] : params) {
            log << "\t" << key << "=" << value << std::endl;
        }
    }
    else{
        log << "The program used values:" << std::endl;
        for (const auto& [key, value] : params) {
            log << "\t" << key << "=" << value << std::endl;
        }
    }
    input_file.close();
    output_file.close();
    // Finally, I record the end time of the processing
    auto finish = std::chrono::high_resolution_clock::now();
    log << "processing took: " << std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
    log << "microseconds" << std::endl << std::endl;
        log.close();

    return 0;
}