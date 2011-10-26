#define DEFINE_LIST(type) \
  typedef struct list_node_##type { \
    struct list_node_##type *next; \
    type *data; \
  } list_node_##type ; \
  typedef struct list_##type { \
      list_node_##type *head; \
      list_node_##type *tail; \
  } list_##type;

#define LIST_PROTOTYPE(type) \
  DEFINE_LIST(type) \
  void list_##type##_insert_after(list_node_##type *node, type *data);\
  void list_##type##_append(list_##type * container, type* data); \
  type* list_##type##_pop(list_##type* container); 

#define LIST_INSERT_AFTER(type) \
 void list_##type##_insert_after(list_node_##type *node, type *data) { \
    	list_node_##type* newnode = malloc(sizeof(*newnode)); \
	list_node_##type* nextnode = node->next; \
	newnode->data= data; \
	newnode->next = nextnode; \
	node->next = newnode; \
  } 

#define LIST_APPEND(type) \
  void list_##type##_append(list_##type * container, type* data) { \
	list_##type##_insert_after(container->tail, data); \
  }

#define LIST_POP(type) \
  type* list_##type##_pop(list_##type* container){ \
	if(container->head==NULL) return NULL; \
	list_node_##type* first = container->head;\
	container->head=first->next; \
	type* data = first->data; \
	free(container->head); \
	\
	if(container->head==NULL) container->tail=NULL; \
  	return data;\
   }
		
#define LIST(type) \
	LIST_INSERT_AFTER(type) \
	LIST_APPEND(type) \
	LIST_POP(type) 



