using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

public class Door : MonoBehaviour, IDropHandler
{
    public string NextLevel;

    private void Update() 
    {
        if (Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }    
    }

    public void OnDrop(PointerEventData eventData)
    {
        if (eventData.pointerDrag != null)
        {
            var item = eventData.pointerDrag.GetComponent<ElementInstance>();
            if (item != null && item.Type == Element.Key)
            {
                LoadNextLevel();
            }
        }
    }

    public void LoadNextLevel()
    {
        SceneManager.LoadScene(NextLevel);
    }
}
