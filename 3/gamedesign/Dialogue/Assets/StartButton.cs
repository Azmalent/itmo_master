using UnityEngine;
using UnityEngine.SceneManagement;

public class StartButton : MonoBehaviour
{
    public void OnButtonClicked()
    {
        SceneManager.LoadScene("DialogueScene");
    }
}
