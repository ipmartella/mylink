const DEFAULT_ENDPOINT = "/bookmarks";
const BOOKMARK_LIST = document.getElementById('bookmark_list');
const ERROR_MSG = document.getElementById('error_msg');

loadBookmarks();

function loadBookmarks() {
    window.fetch(DEFAULT_ENDPOINT)
            .then(response => {
                if (response.ok) {
                    showError("");
                    response.json().then(bookmarks_json => updateBookmarkList(bookmarks_json));
                } else {
                    console.log("Failed to load bookmarks");
                    showError("Couldn't retrieve bookmarks from mylinkserver :(");
                }
            });
}

function showError(msg) {
    ERROR_MSG.innerHTML = msg;
}

function updateBookmarkList(bookmarksJson) {
    clearBookmarkList();

    bookmarksJson.forEach((bookmark, _) => {
                              var new_list_element = createBookmarkListElement(bookmark);
                              BOOKMARK_LIST.append(new_list_element);
                          });
}

function clearBookmarkList() {
    BOOKMARK_LIST.innerHTML = "";
}

function createBookmarkListElement(bookmark) {
    var new_list_element = document.createElement("li");
    var new_link = document.createElement("a");

    new_link.href = bookmark.url;

    if(bookmark.title !== "") {
        new_link.innerHTML = bookmark.title;
    } else {
        new_link.innerHTML = bookmark.url;
    }

    new_list_element.appendChild(new_link);

    return new_list_element;
}
