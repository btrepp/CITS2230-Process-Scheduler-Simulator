#define DEFINE_LIST(type) \
  typedef struct list_node_##type { \
    struct list_node_##type *next; \
    type *data; \
  } list_node_##type ; \
  typedef struct list_##type { \
      list_node_##type *head; \
      list_node_##type *tail; \
  } list_##type; \
  typedef struct list_iterator_##type { \
	list_node_##type *prev; \
	list_node_##type *current; \
	list_##type* container; \
  } list_iterator_##type;

#define LIST_PROTOTYPE(type) \
  DEFINE_LIST(type) \
  void list_##type##_insert_after(list_node_##type *node, type *data);\
  void list_##type##_append(list_##type * container, type* data); \
  type* list_##type##_pop(list_##type* container); \
  void list_##type##_iterator_init(list_iterator_##type* it, list_##type* container); \
  type* list_##type##_next(list_iterator_##type* it); \
  type* list_##type##_examine(list_iterator_##type* it); \
  type* list_##type##_remove(list_iterator_##type* it); 

#define LIST_INSERT_AFTER(type) \
 void list_##type##_insert_after(list_node_##type *node, type *data) { \
	list_node_##type* newnode = malloc(sizeof(*newnode)); \
	newnode->data= data; \
	list_node_##type* nextnode = node->next; \
	newnode->next = nextnode; \
	node->next = newnode; \
  }

#define LIST_APPEND(type) \
  void list_##type##_insert_first(list_##type* container, type* data){ \
	 list_node_##type* newnode = malloc(sizeof(*newnode)); \
         newnode->data= data; \
	 newnode->next=NULL; \
	 container->head = newnode; \
	 container->tail = newnode; \
   } \
  void list_##type##_append(list_##type * container, type* data) { \
	if(container->tail==NULL)\
		list_##type##_insert_first(container,data);\
	else {\
		list_##type##_insert_after(container->tail, data); \
  		container->tail=container->tail->next; \
	 }\
   }
	 

#define LIST_POP(type) \
  type* list_##type##_pop(list_##type* container){ \
	if(container->head==NULL) return NULL; \
	list_node_##type* first = container->head;\
	container->head=first->next; \
	type* data = first->data; \
	free(first); \
	\
	if(container->head==NULL) container->tail=NULL; \
  	return data;\
   }
	

#define LIST_ITERATOR(type) \
   void list_##type##_iterator_init(list_iterator_##type* it, list_##type* container){ \
	it->prev= NULL; \
	it->current = container->head; \
	it->container = container; \
   } \
   \
   type* list_##type##_next(list_iterator_##type* it){\
	if(it->current==NULL) return NULL; \
	it->prev= it->current; \
	it->current = it->current->next; \
   	return list_##type##_examine(it); \
   } \
   type* list_##type##_examine(list_iterator_##type* it){\
	if(it->current!=NULL) \
		return it->current->data; \
	return NULL; \
   } \
   type* list_##type##_remove(list_iterator_##type* it){\
	if(it->current==NULL) return NULL; \
	if(it->prev==NULL) \
		return list_##type##_pop(it->container); \
   	list_node_##type* temp = it->current; \
	it->prev->next = it->current->next; \
	it->current = it->current->next; \
        \
	type* data = temp->data; \
	free(temp); \
	return data; \
   }



	
#define LIST(type) \
	LIST_INSERT_AFTER(type) \
	LIST_APPEND(type) \
	LIST_POP(type) \
	LIST_ITERATOR(type);


