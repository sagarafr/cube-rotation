#pragma once

template<typename T>
class Singelton {
public:
	template<typename U>
	Singelton<T>(const Singelton<U>& singelton) = delete;
	template<typename U>
	Singelton<T>(const Singelton<U>&& singelton) = delete;

	Singelton<T>& operator=(const Singelton<T>& singelton) = delete;
	Singelton<T>& operator=(const Singelton<T>&& singelton) = delete;

	static T* instance() {
		if (mInstance == nullptr) {
			mInstance = new T();
		}
		return mInstance;
	}

	virtual ~Singelton<T>() {
		if (mInstance != nullptr) {
			delete mInstance;
		}
	}

protected:
	static T* mInstance;
	Singelton<T>() {}
};

template<typename T>
T* Singelton<T>::mInstance = nullptr;
