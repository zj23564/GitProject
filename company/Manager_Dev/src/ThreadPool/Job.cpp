/*****************************************************************
*Role:The file manage Linux thread ,include create thread etc.   *
*CopyRight(c):                                                   *
*       flydish,2004,06,25                                       *
*History:                                                        *
*       Create by flydish,2004,06,25                             *
*****************************************************************/

#include "../../include/ThreadPool/Job.h"

CJob::CJob(void)
:m_pWorkThread(NULL)
,m_JobNo(0)
,m_JobName(NULL)
{
}

CJob::~CJob()
{
    if(NULL != m_JobName)
	  {
      delete m_JobName;
	  m_JobName = NULL;
	  }
}

bool CJob::GetTerminated(void)
{
    return false;
}

void CJob::SetJobName(char* jobname)
{
    if(NULL !=m_JobName)
    {
	delete m_JobName;
	m_JobName = NULL;
    }
    if(NULL !=jobname)
    {
	m_JobName = new char[strlen(jobname)+1];
	strcpy(m_JobName,jobname);
    }
}

