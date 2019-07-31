#include "Kernel.h"

int main()
{
	if(Kernel_Init() == -1)
	{
		perror("INit Net call faild");
		return -1;
	}
	//Text();
	ConnectClient(m_pool);
	return 0;
}
