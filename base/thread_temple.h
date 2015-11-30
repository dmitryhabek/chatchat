#ifndef HEADERS_THREAD_TEMPLATE_H_
#define HEADERS_THREAD_TEMPLATE_H_

#include <cstdlib>
#include <pthread.h>
#include <string>
#include <stdexcept>
#include <cxxabi.h>
#include <assert.h>


/// Thread priority:
static int get_thread_policy( pthread_attr_t &attr )
{
    int policy;
    int rs = pthread_attr_getschedpolicy( &attr, &policy );
    assert( rs == 0 );
    return policy;
}

static void set_thread_policy( pthread_attr_t &attr,  int policy )
{
    int rs = pthread_attr_setschedpolicy( &attr, policy );
    assert( rs == 0 );
    get_thread_policy( attr );
}


/// 线程函数模板
// 由于pthread创建线程需要调用静态函数，因此利用该函数模板实现调用成员函数创建线程
template <typename T, void (T::*loop)()>
void* thread_loop(void* param)
{
     T* This = (T*)param;
     This->loop();
     return NULL;
}

///线程类模板
// 定义线程开启、停止、暂停、恢复等方法，提供loop纯虚方法作为线程主函数入口，供派生类实现
// 简化了程序主线程中对子线程的管理
template <class T>
class ThreadTemplate
{
public:
    ThreadTemplate() {
        pthread_mutex_init(&m_lock,NULL);
        setAliveFlag(false);
        setRunningFlag(false);
    }
    virtual ~ThreadTemplate() {
        pthread_mutex_destroy(&m_lock);
    }

    virtual void start() {                  // 开启线程：创建以loop()为线程函数的子线程，设置主线程等待子线程退出
        setAliveFlag(true);
        setRunningFlag(true);
        int return_value = pthread_create(&m_thread_id,NULL,thread_loop<T,&T::loop>,this);

        if(return_value != 0) {
            std::string m_name;
            int status;
            char *class_name = abi::__cxa_demangle(typeid(this).name(), 0, 0, &status);
            m_name.assign(class_name);
            free(class_name);
            std::string error_string = "Cannot Create Thread: ";
            error_string += m_name;
            throw std::runtime_error(error_string);
        }
    }

    virtual void start_custom(int priority) {                  // 开启线程：创建以loop()为线程函数的子线程，设置主线程等待子线程退出
        setAliveFlag(true);
        setRunningFlag(true);

        pthread_attr_t attr;
        struct sched_param sched;
        int rs;
        rs = pthread_attr_init( &attr );
        assert( rs == 0 );
        set_thread_policy(attr,SCHED_RR);
        pthread_attr_getschedparam(&attr,&sched);
        sched.__sched_priority = priority;
        pthread_attr_setschedparam(&attr,&sched);

        int return_value = pthread_create(&m_thread_id,&attr,thread_loop<T,&T::loop>,this);

        if(return_value != 0) {
            std::string m_name;
            int status;
            char *class_name = abi::__cxa_demangle(typeid(this).name(), 0, 0, &status);
            m_name.assign(class_name);
            free(class_name);
            std::string error_string = "Cannot Create Thread: ";
            error_string += m_name;
            throw std::runtime_error(error_string);
        }
    }

    virtual void wait_exit() {              // 等待线程结束
        int exit_value;
        int return_value = pthread_join(m_thread_id,(void**)&exit_value);
        if(return_value != 0) {
            std::string m_name;
            int status;
            char *class_name = abi::__cxa_demangle(typeid(this).name(), 0, 0, &status);
            m_name.assign(class_name);
            free(class_name);
            std::string error_string = "Wait Thread End Error: ";
            error_string += m_name;
            throw std::runtime_error(error_string);
        }
    }

    virtual void stop() {           // 停止线程
        setAliveFlag(false);
    }
    virtual void pause() {          // 暂停线程
        setRunningFlag(false);
    }
    virtual void resume() {         // 恢复线程
        setRunningFlag(true);
    }
    virtual void setAliveFlag(bool flag) {
        pthread_mutex_lock(&m_lock);
        m_alive_flag = flag;
        pthread_mutex_unlock(&m_lock);
    }
    virtual bool getAliveFlag() {
        bool flag;
        pthread_mutex_lock(&m_lock);
        flag = m_alive_flag;
        pthread_mutex_unlock(&m_lock);
        return flag;
    }
    virtual void setRunningFlag(bool flag) {
        pthread_mutex_lock(&m_lock);
        m_running_flag = flag;
        pthread_mutex_unlock(&m_lock);
    }
    virtual bool getRunningFlag() {
        bool flag;
        pthread_mutex_lock(&m_lock);
        flag = m_running_flag;
        pthread_mutex_unlock(&m_lock);
        return flag;
    }

    virtual void loop() = 0;
protected:
    pthread_t m_thread_id;
    pthread_mutex_t m_lock;
    bool m_alive_flag;
    bool m_running_flag;

};

#endif // HEADERS_THREAD_TEMPLATE_H_
