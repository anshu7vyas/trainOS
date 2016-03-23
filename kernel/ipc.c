
#include <kernel.h>


PORT_DEF port[MAX_PORTS];

PORT next_free_port;



PORT create_port()
{
	return create_new_port (active_proc);
}


PORT create_new_port (PROCESS owner)
{
	PORT 	p;

	assert (owner->magic == MAGIC_PCB);
	if (next_free_port == NULL)
		panic ("create_new_port(): PORT full");
	p = next_free_port;
	next_free_port = p->next;
	p->used						= TRUE;
	p->magic 					= MAGIC_PORT;
	p->owner					= owner;
	p->blocked_list_head		= NULL;
	p->blocked_list_tail		= NULL;
	p->open 					= TRUE;
	if (owner->first_port == NULL)
		p->next = NULL;
	else
		p->next = owner->first_port;
	owner->first_port = p;

	return p;
}




void open_port (PORT port)
{
}



void close_port (PORT port)
{
}


void send (PORT dest_port, void* data)
{
}


void message (PORT dest_port, void* data)
{
}



void* receive (PROCESS* sender)
{
}


void reply (PROCESS sender)
{
}


void init_ipc()
{
	int i;

	next_free_port = port;
	for (i = 0; i < MAX_PORTS - 1; i++) {
		port[i].used = FALSE;
		port[i].magic = MAGIC_PORT;
		port[i].next = &port[i + 1];
	}
	port[MAX_PORTS - 1].used = FALSE;
	port[MAX_PORTS - 1].magic = MAGIC_PORT;
	port[MAX_PORTS - 1].next = NULL;
}
