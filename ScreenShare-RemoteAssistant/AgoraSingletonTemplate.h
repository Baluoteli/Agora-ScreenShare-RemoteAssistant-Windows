#ifndef __AGORASINGLETONTEMPLATE_H__
#define __AGORASINGLETONTEMPLATE_H__

template<typename T> class CSingleton
{
public:
	~CSingleton();
	static T* getInstance();

	struct CGrabo
	{
		CGrabo()
		{
			if (nullptr == pCritical_Section)
			{
				pCritical_Section = new CRITICAL_SECTION;
			}

			if (pCritical_Section)
			{
				InitializeCriticalSection(pCritical_Section);
			}
			printf("%s %x\n", __FUNCTION__, (unsigned int)pCritical_Section);
		}

		~CGrabo()
		{
			EnterCriticalSection(pCritical_Section);

			if (pInstance_)
			{
				delete pInstance_;
				pInstance_ = nullptr;
			}

			LeaveCriticalSection(pCritical_Section);
			DeleteCriticalSection(pCritical_Section);

			delete pCritical_Section;
			pCritical_Section = nullptr;
			printf("%s\n", __FUNCTION__);
		}
	};

protected:
	CSingleton();
private:
	static T* pInstance_;
	static LPCRITICAL_SECTION pCritical_Section;
};

template<typename T> LPCRITICAL_SECTION CSingleton<T>::pCritical_Section = nullptr;
template<typename T> T* CSingleton<T>::pInstance_ = nullptr;

template<typename T> CSingleton<T>::CSingleton()
{
	printf("%s\n", __FUNCTION__);
}

template<typename T> CSingleton<T>::~CSingleton()
{
	printf("%s\n", __FUNCTION__);
}

template<typename T> T* CSingleton<T>::getInstance()
{
	if (nullptr == pCritical_Section)
	{
		pCritical_Section = new CRITICAL_SECTION;
	}
	if (nullptr == CSingleton<T>::pInstance_)
	{
		EnterCriticalSection(pCritical_Section);
		CSingleton<T>::pInstance_ = new T;
		LeaveCriticalSection(pCritical_Section);
	}

	return pInstance_;
}

class CSingletonInstance :public CSingleton<CSingletonInstance>
{
public:
	friend CSingleton;
	~CSingletonInstance() {
		printf("%s\n", __FUNCTION__);
	}

	void fun1()
	{
		printf("%s\n", __FUNCTION__);
	}

	void fun2()
	{
		printf("%s\n", __FUNCTION__);
	}

private:
	CSingletonInstance() {
		printf("%s\n", __FUNCTION__);
	}
	//static CSingleton<CSingletonInstance>::CGrabo graboInstance;
};


#endif