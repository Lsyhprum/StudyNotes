 #include <stdio.h>
 int flg[1000];                  /*保存打井或者挖管道信息，0挖管道，1打井 */
int barr[1000][1000];
int arr[1000];
void update(int *st, int n);
int
find(int *arr, int n, int last)/*找出打井费用最低的地*/
{
    int i;
    int min = arr[1];
    int rt = 1;
    for (i = 2; i < n + 1; i++)
            if (arr[i] < min && arr[i] > last) {
                    min = arr[i];
                    rt = i;
            }
    return rt;
}
int
check(int *a, int n)/*检查当前所有土地是否都有水源*/
{
    int i;
    for (i = 1; i < n + 1; i++) {
            if (a[i] > 0) ;
            else
                    break;
    }
    if (i == n + 1)
            return 0;
    else
            return 1;
}
int
main(void)
{
    int i, j, k;
    int n;
    if (freopen("water.in", "r", stdin) == NULL)
            return -1;
    scanf("%d", &n);
    int st[n + 1];          /*保存有水源的地打井或者挖管道的费用 */
    for (i = 1; i < n + 1; i++)
            scanf("%d", &arr[i]);

    for (i = 1; i < n + 1; i++)
            for (j = 1; j < n + 1; j++)
                    scanf("%d", &barr[i][j]);

    for (i = 0; i < n + 1; i++) {
            st[i] = 0;
            flg[i] = 0;
    }
    k = find(arr, n, 0);

    while (check(st, n) != 0) {
            if (st[k] == 0) {
                    st[k] = arr[k];
                    flg[k] = 1;
                    printf("第%d块地打井 \n", k);
            }
            for (i = 1; i < n + 1; i++) {
                    if (st[i] > 0)
                            continue;
                    int flag = 1;
                    if (i == k || barr[i][k] > arr[i])
                            continue;
                    else {
                            for (j = 1; j < n + 1; j++) {
                                    if (i != j && barr[i][j] < barr[i][k]
                                        && j != k) {
                                            flag = 0;
                                            break;
                                    }
                            }
                            if (flag == 1 && st[i] == 0) {
                                    st[i] = barr[i][k];
                                    printf
                                        ("第%d块地与第%d块地挖管道\n",
                                         i, k);
                            }
                    }
            }
            update(st, n);
            k = find(arr, n, st[k]);
    }

    for (i = 1; i < n + 1; i++)
            printf("%d ", st[i]);
    printf("\n");
    return 0;
}
/*当i块地接通水源以后别的地可以通过与挖它管道接通水源
 * 本函数作用是确定没有水源的地与i块地之间的管道*/
void
update(int *st, int n)
{
    int i, j, k, l;
    for (l = 1; l < n + 1; l++) {
            if (st[l] > 0 && flg[l] == 0)
                    k = l;
            else
                    continue;

            for (i = 1; i < n + 1; i++) {
                    if (st[i] > 0 && flg[i] == 1)
                            /*flg[i]=1，打井的地，费用信息不能更新 */
                            continue;
                    int flag = 1;
                    /*跳过与第i块间管道费用比打井贵的地 */
                    if (i == k || barr[i][k] > arr[i])
                            continue;
                    else {
                             /**/ for (j = 1; j < n + 1; j++) {
                                    if (i != j && barr[i][j] < barr[i][k]
                                        && j != k) {
                                            flag = 0;
                                            break;
                                    }
                            }
                            if (flag == 1 && st[i] == 0 && flg[i] == 0) {
                                    st[i] = barr[i][k];
                                    printf
                                        ("第%d块地与第%d块地挖管道\n",
                                         i, k);

                            }
                    }
            }
    }
}
