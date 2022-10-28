using UnityEngine;

public class EnemySpawner : MonoBehaviour
{
    public GameObject enemyPrefab;
    public GameObject toughEnemyPrefab;
    public GameObject fastEnemyPrefab;

    private Transform playerPos;
    private float spawnsPerSecond = 1;
    private float timeBetweenSpawns = 1;
    private float timeUntilNextSpawn = 0;

    void Start()
    {
        playerPos = GameObject.FindGameObjectWithTag("Player").transform;
    }

    void Update()
    {
        spawnsPerSecond = 1 + Mathf.Sqrt(Time.timeSinceLevelLoad) / 8;
        timeBetweenSpawns = 1 / spawnsPerSecond;

        timeUntilNextSpawn -= Time.deltaTime;
        while (timeUntilNextSpawn <= 0)
        {
            timeUntilNextSpawn += timeBetweenSpawns;
            Spawn();
        }
    }

    void Spawn()
    {
        float x, y;
        Vector2 a, b;

        do
        {
            x = Random.Range(-38, 38);
            y = Random.Range(-18, 18);
            
            a = new Vector2(x, y);
            b = new Vector2(playerPos.position.x, playerPos.position.y);
        } while (Vector2.Distance(a, b) < 5);

        GameObject prefab = enemyPrefab;
        
        float f = Random.value;
        if (f > 0.8) 
        {
            prefab = toughEnemyPrefab;
        }
        else if (f > 0.5)
        {
            prefab = fastEnemyPrefab;
        }

        Instantiate(prefab, new Vector3(x, y, 0), Quaternion.Euler(0, 0, 0));
    }
}
