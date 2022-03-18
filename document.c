/*Eloho Etareri
  UID: 117262667
  Directory ID: eetareri*/

#include <stdio.h>
#include "document.h"
#include <string.h>
#include <ctype.h>

int init_document(Document *doc, const char *name) {
  
  /*The function returns FAILURE because doc or name is null*/
  if ((doc == NULL) || (name == NULL)) {
    return FAILURE;
  }

  /*Initializes *doc to have 0 paragraphs and uses strcpy
   to set the documents name to the one provided in
  the parameter*/
 if ((strlen(name) >= 1) &&  (strlen(name) <= MAX_STR_SIZE)) {
    doc->number_of_paragraphs = 0;
    strcpy(doc->name, name); 
    return SUCCESS;
  } else {
    return FAILURE;
  }



}

/*This function takes a document as a parameter and resets
the number of paragraphs in the document to 0. Returns FAILURE
if the document is NULL and returns SUCCESS otherwise.*/
int reset_document(Document *doc) {
  
  if (doc != NULL) {
    doc->number_of_paragraphs = 0;
    return SUCCESS;
  } else {
    return FAILURE;
  }
  
}

/*This function takes a document as a parameter and prints
basic info about the document as well as the contents of
the document. Returns FAILURE if the document provided
is NULL. Returns SUCCESS otherwise. */
int print_document(Document *doc) {
  int i, j;
  if (doc != NULL) {
    printf("Document name: \"%s\"\n", doc->name);
    printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
    
    /*i represents each paragraph and j represents each line in 
     the paragraph. The newline is only printed if there are 
    more paragraphs left. Doesn't print a newline after the last paragraph*/
    for (i = 0; i < doc->number_of_paragraphs; i++) {
    
      if (doc->paragraphs[i].number_of_lines > 0) {
	for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
	  printf("%s\n", doc->paragraphs[i].lines[j]);
	}
      }
	if (i < doc->number_of_paragraphs-1) {
	  printf("\n");
      }
    }

    return SUCCESS;
  
  } else {
   
    return FAILURE;

  }
}

/*This function adds a new paragraph after the paragraph number 
specified in the parameter. Returns failure if the document
is null, the document already has the max number of paragraphs 
or an invalid paragraph number is provided*/
int add_paragraph_after(Document *doc, int paragraph_number) {
  int i, total_paragraphs;
  if (doc != NULL) {
    total_paragraphs = doc->number_of_paragraphs;
 
  /*Checking that the provided parameters are valid*/
    if ((total_paragraphs != MAX_PARAGRAPHS) && (paragraph_number >= 0) && 
	(paragraph_number <= total_paragraphs)) {
    
      /*Adding a paragraph to a doc with no paragraphs*/
      if ((paragraph_number == 0) && (total_paragraphs == 0)) {
	  doc->paragraphs[0].number_of_lines = 0;
      
      } /*Adding a paragraph to the end of a doc that already has paragraphs*/
      else if ((paragraph_number > 0) && (paragraph_number == total_paragraphs)) {
	doc->paragraphs[paragraph_number].number_of_lines = 0;
	
      } else {

	for (i = total_paragraphs-1; i >= paragraph_number; i--) {
	  doc->paragraphs[i+1] = doc->paragraphs[i];
	}
	doc->paragraphs[paragraph_number].number_of_lines = 0;
      }
      
      doc->number_of_paragraphs++;
      return SUCCESS;
    }
    return FAILURE;
  } else {
  
    return FAILURE;
  }
}

/*This function adds a new line after the specified line_number.
If the line number is 0 the line is added at the start of the paragraph.
Returns FAILURE if doc or new_line is NULL. Also returns failure if the
paragraph number or line_number are invalid. Returns SUCCESS otherwise*/
int add_line_after(Document *doc, int paragraph_number, int line_number, const char *new_line) {
  int i,total_lines;
  Paragraph *par_ptr;
  
  if ((doc == NULL) || (new_line == NULL)) {
    return FAILURE;
  }

  par_ptr = &doc->paragraphs[paragraph_number-1];
  total_lines = par_ptr->number_of_lines;

  if ((paragraph_number > 0) && (paragraph_number <= doc->number_of_paragraphs)&&
      (total_lines < MAX_PARAGRAPH_LINES) && (line_number >= 0) && 
      (line_number <= total_lines)) {
    
    /*Adding a line to a paragraph with no lines*/
    if ((line_number == 0) && (total_lines == 0)) {
      strcpy(par_ptr->lines[0], new_line);
    } 
    /*Adding a line to the end of a paragraph with existing lines*/
    else if ((line_number > 0) && (line_number == total_lines)) {
      strcpy(par_ptr->lines[line_number], new_line); 
   
    } else {
      /*Moves all the other lines forward one and places the new line in 
       the specified location*/
      for (i = total_lines-1; i >= line_number; i--) {
	/* printf("New line:\n");*/
	strcpy(par_ptr->lines[i+1], par_ptr->lines[i]);
      }
      strcpy(par_ptr->lines[line_number], new_line);
    }
    par_ptr->number_of_lines++;
    
    return SUCCESS;
    
    
  } else {
    /*printf("DIDNT WORK");*/
    return FAILURE;
  }
			  
}

/*This function returns the number of lines in the specified paragraph using 
the number_of_lines out parameter. Returns FAILURE  if doc or number_of_lines is NULL.
Also returns FAILURE if paragrap_number is invalid. Returns SUCCESS otherwise.*/
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines) {

  if ((doc != NULL) && (number_of_lines != NULL)) {
    /*If the parameters are valid, get the number of lines of the paragraph*/
    if ((paragraph_number > 0) && (paragraph_number <= doc->number_of_paragraphs)) {
      *number_of_lines = doc->paragraphs[paragraph_number-1].number_of_lines;
    }

    return SUCCESS;

  } else {
    return FAILURE;

  }
}

/*This function adds a new line to the end of the specified paragraph*/
int append_line(Document *doc, int paragraph_number, const char *new_line) {
  Paragraph *par_ptr;
  int last_line;

  if ((doc!= NULL) && (new_line != NULL)) {
    /*Checking that the paremeters are valid*/
    if ((paragraph_number > 0) && (paragraph_number <= doc->number_of_paragraphs)) {
      par_ptr = &doc->paragraphs[paragraph_number-1];
      last_line = par_ptr->number_of_lines;
     
      /*Calls add_line_after on the last line of the paragraph*/
      if (last_line < MAX_PARAGRAPH_LINES) {
	add_line_after(doc, paragraph_number, last_line, new_line);
	return SUCCESS;
      }
    }
  }
    return FAILURE;
}

/*This function removes the specified line from the paragraph. Returns
FAILURE if doc is NULL or if the parameters are invalid. Returns SUCCESS
otherwise.*/
int remove_line(Document *doc, int paragraph_number, int line_number) {
  Paragraph *par_ptr;
  int number_of_lines, i = 0;
  
  if (doc != NULL) {
    /*Checking that the parameters are valid*/
    if ((paragraph_number > 0) && (paragraph_number <= doc->number_of_paragraphs)){
      par_ptr = &doc->paragraphs[paragraph_number-1];
      
      if ((line_number > 0) && (line_number <= par_ptr->number_of_lines)) {
	number_of_lines = 0;
	get_number_lines_paragraph(doc, paragraph_number, &number_of_lines);
	
	/*Overwrites the line to remove with the line right after it*/
	for (i = line_number-1; i < number_of_lines; i++) {
	  strcpy(par_ptr->lines[i],par_ptr->lines[i+1]);
	}
	(par_ptr->number_of_lines)--;
	return SUCCESS;
      }
    }
  }
    return FAILURE;
}

/*This function adds the first data_lines number of rows from the 
data array to the document, starting a new paragraph at the beginning of
the paragraph. If the result of load_document will violate the 
MAX_PARAGRAPHS, the document will remain unchanged. Returns FAILURE in this 
case. Otherwise returns SUCCESS */
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines) {
  int i, num_of_paragraphs, num_paras_to_add, num_lines;
  

  if ((doc != NULL) && (data != NULL) && (data_lines > 0)) {
    num_of_paragraphs = doc->number_of_paragraphs;
    num_paras_to_add = 1;
    num_lines = 0;
    
    /*Determines if it is necessary to load the document*/
    for (i = 0; i < data_lines; i++) {
      /*If data[i] is an empty row, increment num_paras_to_add by 1*/
      if (strcmp(data[i], "") == 0) {
	num_paras_to_add++;
	/*Resets num_lines to 0 after finding a new paragraph*/
	num_lines = 0;
	/*If loading data violates max number of allowed paragraphs 
	 return FAILURE*/
	if (num_paras_to_add + num_of_paragraphs > MAX_PARAGRAPHS) {
	  return FAILURE;
	}
      
      } else {
	/*Increments num_lines by 1 if data[i] is not an empty row*/
	num_lines++;
	/*Returns FAILURE if the current paragraph has too many lines*/
	if (num_lines > MAX_PARAGRAPH_LINES) {
	  return FAILURE;
	}
    }   
  }
    /*Adding the paragraphs from data to the document*/
    add_paragraph_after(doc, 0);
    num_paras_to_add = 1;
    for (i = 0; i < data_lines; i++) {
      if (strcmp(data[i], "") == 0) {
	add_paragraph_after(doc, num_paras_to_add++);
      } else {
	append_line(doc, num_paras_to_add, data[i]);

      }
    }
    return SUCCESS;
  } 
  return FAILURE;
    
}

/*Auxiliary function for replace_text. Takes a string and replaces
the text just in that string*/
int replace_in_line(char *line, const char *target, const char *replacement) {
  char *line_ptr, *target_location, new_string[MAX_STR_SIZE+1] = "";
  int length_of_target, length;

  line_ptr = line;
  length_of_target = strlen(target);
  target_location = strstr(line_ptr, target);
 

  while (target_location != NULL) {
    length = target_location - line_ptr;
    
    /*Copying everything between the pointer and the target 
     to the new string*/
    strncat(new_string, line_ptr, length);
    /*Copies the replacement string to the end of the new string*/
    strcat(new_string, replacement);
    

    /*placing the pointer after the target*/
    line_ptr += length + length_of_target; /*line_ptr = &target_location????*/
    /*Finding the next occurence of the target*/
    target_location = strstr(line_ptr, target);
  }
  strcat(new_string, line_ptr);
  strcpy(line, new_string);
  return 0;
}

/*This function replaces all appearances of the text target in the
document with the replacement text. Returns FAILURE if doc, target
or replacement NULL*/
int replace_text(Document *doc, const char *target, const char *replacement) {
  int i,j;
  Paragraph *par_ptr;
 
 if ((doc != NULL) && (target != NULL) && (replacement != NULL)) {
   /*Uses the replace_in_line auxiliar function to
    replace the text in each line*/
    for (i = 0; i < doc->number_of_paragraphs; i++) {
      par_ptr = &doc->paragraphs[i];
      for (j = 0; j < par_ptr->number_of_lines; j++) {
	replace_in_line(par_ptr->lines[j], target, replacement);
      }

    }

    return SUCCESS;
  }
  return FAILURE;


}
/*This function highlights every appearance of the text 
target in the document. Returns FAILURE if doc or target
is NULL. Returns SUCCESS otherwise.*/
int highlight_text(Document *doc, const char *target){
  char text_to_highlight[MAX_STR_SIZE+1] = "";
  
  if ((doc != NULL) && (target != NULL)) {
    strcat(text_to_highlight, HIGHLIGHT_START_STR);
    strcat(text_to_highlight, target);
    strcat(text_to_highlight, HIGHLIGHT_END_STR);
    /*Uses replace_text to replace the target with
     its highlighted version*/
    replace_text(doc, target, text_to_highlight);
    return SUCCESS;
  }
  return FAILURE;
}

/*This function removes every appearances of text target
in the document. Returns FAILURE if doc or target is NULL.
Returns SUCCESS otherwise*/
int remove_text(Document *doc, const char *target) {
  
  if ((doc != NULL) && (target != NULL)) {
    replace_text(doc, target, "");
    return SUCCESS;
  }
  return FAILURE;

}

int load_file(Document *doc, const char *filename) {
  int i = 1, j, blank_line = 1;
  char data[MAX_PARAGRAPH_LINES][MAX_STR_SIZE+1], line[MAX_STR_SIZE+1];
  FILE *input;
  if ((doc ==  NULL) || (filename == NULL)) {
    return FAILURE;
  } else {
   
    if ((input = fopen(filename, "r")) == NULL) {
      return FAILURE;
    }
    
    add_paragraph_after(doc, 0);
    while (fgets(line, MAX_STR_SIZE + 1, input) != NULL) {
      line[strlen(line)-1] = '\0';
      /* strcpy(data[i], line);*/
      blank_line = 1;
      for (j = 0; line[j] != '\0'; j++) {
	if (isspace(line[j]) == 0) {
	  blank_line = 0;
	  break;
	}
      }
      /*if (blank_line == 1) {
	add_paragraph_after(doc, i);
	printf("check");
	}*/
     
      /* blank_line = 1; */
    
   
      if ((blank_line == 1) || strcmp(line, "") == 0) {
  
      add_paragraph_after(doc, i);
      i++;
      
      
      } else {
      append_line(doc, i, line);
      }
    }


    /* load_document(doc, data, i);*/
   
  }
  fclose(input);
  return SUCCESS;
  }




int save_document(Document *doc, const char *filename) {
  int i, j;
  FILE *output_stream;

  if ((doc ==  NULL) && (filename == NULL)) {
    return FAILURE;
  } else {
   
    if ((output_stream = fopen(filename, "w")) == NULL) {
      return FAILURE;
    }
    
  
    fprintf(output_stream, "Document name: \"%s\"\n", doc->name);
    fprintf(output_stream, "Number of Paragraphs: %d\n", doc->number_of_paragraphs);
    for (i = 0; i < doc->number_of_paragraphs; i++) {
      
      if (doc->paragraphs[i].number_of_lines > 0) {
	for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
	  fprintf(output_stream, "%s\n", doc->paragraphs[i].lines[j]);
      }
    }
   
      if (i < doc->number_of_paragraphs-1) {
	fprintf(output_stream,"\n");
      }
    }
    
    fclose(output_stream);
    return SUCCESS;

  }  
  

}
