

bool findDuplicate(vector<int> & ans, const int & target) {
    for (int i = 0; i < ans; i++) {
        if (ans[i] == target) {
            return true;
        }
    }

    return false;
}

vector<int> sol(vector<int> & duplicatedNumbers) {
    vector<int> ans;

    for (int i = 0; i < duplicatedNumbers.size(); i++) {
        if (findDuplicate(ans, duplicatedNumbers[i])) {
            continue;
        }
        ans.push_back(duplicatedNumbers[i]);
    }

    return ans;
}
