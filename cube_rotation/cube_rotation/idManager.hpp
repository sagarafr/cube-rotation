#pragma once

#include <map>
#include <string>
#include <exception>
#include <GL/freeglut.h>

template<typename T>
class IDManager {
public:
	IDManager<T>() {}

	IDManager<T>(const IDManager<T>& manager) = delete;
	IDManager<T>(const IDManager<T>&& manager) = delete;

	IDManager<T>& operator=(const IDManager<T>& manager) = delete;
	IDManager<T>& operator=(const IDManager<T>&& manager) = delete;

	virtual ~IDManager<T>() {
		for (auto item : mElements) {
			delete item.second;
		}
	}

	GLuint getID(const std::string& id) const {
		auto search(mElements.find(id));
		if (search != mElements.cend()) {
			return getIDFromElement((search->second));
		}
		throw std::domain_error(id + " not found");
	}

	T* getElement(const std::string& id) const {
		auto search(mElements.find(id));
		if (search != mElements.cend()) {
			return search->second;
		}
		throw std::domain_error(id + " not found");
	}

	void setElement(const std::string& id, T * const element) {
		mElements.emplace(id, element);
	}

protected:
	virtual GLuint getIDFromElement(const T* elements) const = 0;
	std::map<std::string, T*> mElements;
};
