Node* BuildTree() {
    if (now < 0) return NULL;

    while (str[now] == ' ') {
        now--;
    }

    Node* root = NULL;

    if (str[now] == '-' || str[now] == '+') {
        root = create(-1, str[now]);
        root->type = 0;
        now--;
        root->right_child = BuildTree(); // Right child first (postfix)
        root->left_child = BuildTree();  // Left child second (postfix)
    } else {
        int num = 0;
        int sign = 1;

        while (now >= 0 && (str[now] >= '0' && str[now] <= '9' || str[now] == '-')) {
            if (str[now] == '-') {
                sign = -1;
            } else {
                num = num * 10 + (str[now] - '0');
            }
            now--;
        }
        num *= sign;

        root = create(num, ' ');
        root->type = 1;
    }

    return root;
}
