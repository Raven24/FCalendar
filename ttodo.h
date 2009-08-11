#include "task.h"

#ifndef TTODO_H
#define TTODO_H

class Task;

class TTodo : public Task
{
public:
    TTodo();

	void setPercentComplete(int comp);
	void setComplete(bool comp);

	int getPercentComplete();
	bool isComplete();

private:
	int m_complete;
};

#endif // TTODO_H
