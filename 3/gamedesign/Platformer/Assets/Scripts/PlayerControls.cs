using UnityEngine;
using UnityEngine.SceneManagement;

[RequireComponent( typeof(Player) )]
public class PlayerControls : MonoBehaviour
{
    const int LEFT = -1;
    const int IDLE = 0;
    const int RIGHT = 1;

    private Player player;

    void Start()
    {
        player = GetComponent<Player>();
    }

    void Update()
    {
        if (Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.A)) 
        {
            player.SetMovingDirection(LEFT);
        }
        else if (Input.GetKey(KeyCode.RightArrow) || Input.GetKey(KeyCode.D)) 
        {
            player.SetMovingDirection(RIGHT);
        }
        else 
        {
            player.SetMovingDirection(IDLE);
        }

        if (Input.GetKey(KeyCode.DownArrow) || Input.GetKey(KeyCode.S))
        {
            player.DropDown();
        }

        if (Input.GetKeyDown(KeyCode.Space) || Input.GetKeyDown(KeyCode.UpArrow) || Input.GetKeyDown(KeyCode.W)) 
        {
            player.Jump();
        }

        if (Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
}
