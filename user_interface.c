#include <stdio.h>
#include <string.h>
#include <sysexits.h>
#include <stdlib.h>
#include <ctype.h>
#include "document.h"
#define MAX_LINE_LENGTH 1023

/*Assumes a valid line is passed, this function adds a paragraph
to the document. Prints "invalid command" if the paragraph
number is missing, is negative, or does not represent a number. */
void check_add_paragraph_after(Document *doc, const char *line) {
  int num_args, par_num;
  char extra_info[MAX_LINE_LENGTH +1], command[MAX_LINE_LENGTH+1];
  
  num_args = sscanf(line, "%s%d%s", command, &par_num, extra_info);
  if (strcmp("add_paragraph_after", command) != 0) {
    printf("Invalid Command\n");
    return;
  } else if ((num_args == 2) && (par_num >= 0)) {
    if (add_paragraph_after(doc, par_num) == FAILURE) {
      printf("add_paragraph_after failed\n");
    }
  } else {
    printf("Invalid Command\n");
  }
  return;

}

/*Assumes a valid line is passed, this function adds a line
to the specified paragraph. Prints "invalid command" if the paragraph or
line number is missing, is negative, or does not represent a number. */
void check_add_line_after(Document *doc, const char *line) {
  int num_args, par_num, line_num;
  char command[MAX_LINE_LENGTH+1], line_to_add[MAX_LINE_LENGTH +1], *ptr;

  num_args = sscanf(line, "%s%d%d%s", command, &par_num, &line_num, line_to_add);
  /*Checks valid arguments passed to the function*/
  
  if (strcmp("add_line_after", command) != 0) {
    printf("Invalid Command\n");
    return;
  } else if ((num_args == 4) && (par_num > 0) && (line_num >= 0)) {
    if ((ptr = strstr(line, "*")) != NULL) {
      ptr++;
      ptr[strlen(ptr)-1] = '\0';
      if (add_line_after(doc, par_num, line_num, ptr) == FAILURE) {
	printf("add_line_after failed\n");
      }
    }
  } else {
    printf("Invalid Command\n");
  }
  return;
}

void check_print_document(Document *doc, const char *line) {
  int num_args;
  char command[MAX_LINE_LENGTH +1], extra_info[MAX_LINE_LENGTH +1];

  num_args = sscanf(line, "%s%s", command, extra_info);
  if (strcmp("print_document", command) != 0) {
    printf("Invalid Command\n");
    return;
  } else if (num_args == 1) {
    if(print_document(doc) == FAILURE) {
      printf("print_document failed\n");
    }
  } else {
    printf("Invalid Command\n");
  }
  return;
}

void check_quit(const char *line) {
  int num_args;
  char command[MAX_LINE_LENGTH + 1], extra_info[MAX_LINE_LENGTH + 1];

  num_args = sscanf(line, "%s%s", command, extra_info);

  if ((strcmp("quit", command) != 0) && (strcmp("exit", command) != 0)) {
    printf("Invalid Command\n");
    return;
  } else if (num_args == 1) {
      exit(EXIT_SUCCESS);
  } else {
    printf("Invalid Command\n");
  }
  return;
  
}

void check_append_line(Document *doc, const char *line){
  int num_args, par_num;
  char command[MAX_LINE_LENGTH +1], line_to_add[MAX_LINE_LENGTH + 1], *ptr;

  num_args = sscanf(line, "%s%d%s", command, &par_num, line_to_add);

  if (strcmp("append_line", command) != 0) {
    printf("Invalid Command\n");
    return;
  }else if ((num_args == 3) && (par_num > 0)) {
    if ((ptr = strstr(line, "*")) != NULL) {
      ptr++;
      ptr[strlen(ptr)-1] = '\0';
      if (append_line(doc, par_num, ptr) == FAILURE) {
	printf("append_line failed\n");

      }
    }
  } else {
    printf("Invalid Command\n");
  }
  return;

}


void check_remove_line(Document *doc, const char *line) {
  int num_args, par_num, line_num;
  char command[MAX_LINE_LENGTH + 1], extra_info[MAX_LINE_LENGTH + 1];

  num_args = sscanf(line, "%s%d%d%s", command, &par_num, &line_num, extra_info);

  if (strcmp("remove_line", command) != 0) {
    printf("Invalid Command\n");
    return;
  } else if ((num_args == 3) && (par_num > 0) && (line_num > 0)) {
    if (remove_line(doc, par_num, line_num) == FAILURE) {
      printf("remove_line failed\n");
    }
  } else {
    printf("Invalid Command\n");
  }
  return;
}


void check_load_file(Document *doc, const char *line) {
  int num_args;
  char command[MAX_LINE_LENGTH + 1], filename[MAX_LINE_LENGTH + 1],
    extra_info[MAX_LINE_LENGTH + 1];

  num_args = sscanf(line, "%s%s%s", command, filename, extra_info);

  if (strcmp("load_file", command) != 0) {
    printf("Invalid Command\n");
    return;
  } else if (num_args == 2) {
    if (load_file(doc, filename) == FAILURE) {
      printf("load_file failed\n");
    }
  } else {
    printf("Invalid Command\n");
  }
  return;
}


void check_replace_text(Document *doc, const char *line) {
  int num_args, length_of_target, length_of_rep;
  char command[MAX_STR_SIZE + 1], *target_ptr, *rep_ptr,
    new_targ[MAX_STR_SIZE + 1] = "",  new_rep[MAX_STR_SIZE + 1] = "", 
    extra_info[MAX_STR_SIZE + 1];

  

  num_args = sscanf(line, "%s%s", command, extra_info);
 
  

    if (strcmp("replace_text", command) != 0) {
      printf("Invalid Command\n");
      return;
    } else if (num_args == 2) {
    
      if (strstr(line, "\"") == NULL) {
	printf("Invalid Command\n");
	return;
      }
      target_ptr = strstr(line, "\"") + 1;
      
      
       if (strstr(target_ptr, "\"") == NULL) {
	printf("Invalid Command\n");
	return;
      }
      length_of_target = strstr(target_ptr, "\"") - target_ptr; /*Expect 5*/
     
      
      strncat(new_targ, target_ptr, length_of_target);
     

      rep_ptr = target_ptr + length_of_target + 1;
      if (strstr(rep_ptr, "\"") == NULL) {
	printf("Invalid Command\n");
	return;
      }
      rep_ptr = strstr(rep_ptr, "\"") + 1;
      if (strstr(rep_ptr, "\"") == NULL) {
	printf("Invalid Command\n");
	return;
      }
      length_of_rep = strstr(rep_ptr, "\"") - rep_ptr;
      strncat(new_rep, rep_ptr, length_of_rep);


      
       /*Removing the quotation marks from the replacement*/
      /* rep_ptr = replacement + 1;
      length_of_rep = strlen(replacement) - 2;
      strncat(new_rep, rep_ptr, length_of_rep);*/
	
      if (replace_text(doc, new_targ, new_rep) == FAILURE) {
	printf("replace_text failed\n");
      }
    } else {
      printf("Invalid Command\n");
    }
    return;
}

void check_highlight_text(Document *doc, const char *line) {
  int num_args, length_of_target;
  char command[MAX_LINE_LENGTH + 1], *target_ptr,
    new_targ[MAX_LINE_LENGTH + 1] = "",
    extra_info[MAX_LINE_LENGTH + 1];

  num_args = sscanf(line, "%s%s", command, extra_info);

  if (strcmp("highlight_text", command) != 0) {
    printf("Invalid Command\n");
    return;
  } else if (num_args == 2) {
    /* target_ptr = target + 1;
     length_of_target = strlen(target) - 2;
     strncat(new_targ, target_ptr, length_of_target);
     printf("new targ: %s\n", new_targ);*/
    
     
      target_ptr = strstr(line, "\"") + 1;
      length_of_target = strstr(target_ptr, "\"") - target_ptr; /*Expect 5*/
      strncat(new_targ, target_ptr, length_of_target);
    
    


     if (highlight_text(doc, new_targ) == FAILURE) {
       printf("highlight_text failed\n");
     }
  } else {
    printf("Invalid Command\n");
  }
  return;

}

void check_remove_text(Document *doc, const char *line) {
 int num_args, length_of_target;
  char command[MAX_LINE_LENGTH + 1], extra_info[MAX_LINE_LENGTH + 1],
    *target_ptr, new_targ[MAX_LINE_LENGTH + 1] = "";

  num_args = sscanf(line, "%s%s", command, extra_info);

  if (strcmp("remove_text", command) != 0) {
    printf("Invalid Command\n");
    return;
  } else if (num_args == 2) {
    
     
    target_ptr = strstr(line, "\"") + 1;
    length_of_target = strstr(target_ptr, "\"") - target_ptr; /*Expect 5*/
    strncat(new_targ, target_ptr, length_of_target);


   




 /* target_ptr = target + 1;
     length_of_target = strlen(target) - 2;
     strncat(new_targ, target_ptr, length_of_target);
     printf("new targ: %s\n", new_targ);*/
     


     if (remove_text(doc, new_targ) == FAILURE) {
       printf("remove_text failed\n");
     }
  } else {
    printf("Invalid Command\n");
  }
  return;

}




void check_save_document(Document *doc, const char *line) {
  int num_args;
  char command[MAX_LINE_LENGTH + 1], filename[MAX_LINE_LENGTH + 1],
    extra_info[MAX_LINE_LENGTH + 1];

  num_args = sscanf(line, "%s%s%s", command, filename, extra_info);
  
  if (strcmp("save_document", command) != 0) {
    printf("Invalid Command\n");
    return; 
  } else if (num_args == 2) {
    if (save_document(doc, filename) == FAILURE) {
      printf("save_document failed\n");
    }
  } else {
    printf("Invalid Command\n");
  }
  return;
}


void check_reset_document(Document *doc, const char *line) {
  int num_args;
  char command[MAX_LINE_LENGTH + 1], extra_info[MAX_LINE_LENGTH + 1];

  num_args = sscanf(line, "%s%s", command, extra_info);
  
  if (strcmp("reset_document", command) != 0) {
    printf("Invalid Command\n");
    return; 
  } else if (num_args == 1) {
    if (reset_document(doc) == FAILURE) {
      printf("reset_document failed\n");
    }
  } else {
    printf("Invalid Command\n");
  }
  return;
}




void check_valid_line(Document *doc, const char *line) {
  const char *cmnd_ptr, *cmnd_string;
  char first_char;
  int i;


  for (i = 0; line[i] != '\n'; i++) {
  
    if (isspace(line[i]) == 0) { /*If the current char is a not a space*/
      first_char = line[i];
      
      if ((first_char != '#') && (first_char != '\n')) {/*If this isnt a comment
							  line or blank line*/
	/*cmnd_string = &line[i];*/
	break;
      } else {
	return;
      }

    }
  }
 
  if (line[i] != '\n') { /*The initial loop ended after finding the first char*/
    cmnd_string = &line[i];
    if (strstr(cmnd_string, "#") != NULL) {
      printf("Invalid Command\n");
    }
    if ((cmnd_ptr = strstr(cmnd_string, "add_paragraph_after")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_add_paragraph_after(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "add_line_after")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
        check_add_line_after(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    } 
    else if ((cmnd_ptr = strstr(cmnd_string, "print_document")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_print_document(doc, line); /*Does this really need the line?*/
      }else{
	printf("Invalid Command\n");
      }
    }
    else if (((cmnd_ptr = strstr(cmnd_string, "quit")) != NULL) ||
      ((cmnd_ptr = strstr(cmnd_string, "exit")) != NULL)) {
      if (cmnd_ptr - cmnd_string == 0) {
        check_quit(line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "append_line")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_append_line(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "remove_line")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_remove_line(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "load_file")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_load_file(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "replace_text")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_replace_text(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "highlight_text")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_highlight_text(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "remove_text")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_remove_text(doc,line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "save_document")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
	check_save_document(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    }
    else if ((cmnd_ptr = strstr(cmnd_string, "reset_document")) != NULL) {
      if (cmnd_ptr - cmnd_string == 0) {
        check_reset_document(doc, line);
      }else{
	printf("Invalid Command\n");
      }
    } else {

      printf("Invalid Command\n");

    }

  }
  return;
}

int main(int argc, char **argv) {
  FILE *input;
  char line[MAX_LINE_LENGTH + 1];
  Document doc;
  const char *doc_name = "main_document";
  
  if (argc == 1) { /*No filename argument. [[[Is this the correct way?]]]*/
    printf("> ");
    input = stdin; /*[[[Should I be using scanf after this?]]]*/

  } else if (argc == 2) { /*User enters a filename as an arguument*/
    input = fopen(argv[1], "r");
    
    if (input == NULL) { /*Error opening file, program exits*/
      fprintf(stderr, "%s cannot be opened.", argv[1]);
      return EX_OSERR;
    }
  } else {
    fprintf(stderr, "Usage: user_interface\n");
    fprintf(stderr, "Usage user_interface <filename>\n");
    return EX_USAGE;
  }

  init_document(&doc, doc_name);

  fgets(line, MAX_LINE_LENGTH + 1, input);
  while (!feof(input)) {
    check_valid_line(&doc, line);
    if(argc == 1){
      printf("> ");
    }
    fgets(line, MAX_LINE_LENGTH + 1, input);
    }
  fclose(input);
  return 0;
}





