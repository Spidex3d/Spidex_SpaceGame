#pragma once
class SelectedObjectManager {
public:
    static SelectedObjectManager& Instance() {
        static SelectedObjectManager instance;
        return instance;
    }

    BaseModel* GetSelectedData() const {
        return selectedData;
    }

    void SetSelectedData(BaseModel* data) {
        selectedData = data;
    }

private:
    SelectedObjectManager() : selectedData(nullptr) {}
    ~SelectedObjectManager() {}

    SelectedObjectManager(const SelectedObjectManager&) = delete;
    SelectedObjectManager& operator=(const SelectedObjectManager&) = delete;

    BaseModel* selectedData;
};
