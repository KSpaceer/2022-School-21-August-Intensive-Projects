#include "documentation_module.h"

int validate(char* data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

int *check_available_documentation_module(int (*validate)(char*), int document_count, ...) {
  va_list all_documents;
  va_start(all_documents, document_count);
  int *availability_mask = malloc(document_count * sizeof(int));
  for (int i = 0; i < document_count; i++) {
    char* document = va_arg(all_documents, char*);
    availability_mask[i] = validate(document);
  }
  va_end(all_documents);
  return availability_mask;
}

