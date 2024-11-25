// Seleziona elementi
const openSidebarBtn = document.getElementById('navBtn');
const closeSidebarBtn = document.getElementById('closeSidebarBtn');
const sidebar = document.getElementById('sidebar');
const overlay = document.getElementById('overlay');

// Mostra la sidebar e l’overlay
openSidebarBtn.addEventListener('click', () => {
  sidebar.classList.add('show');
  overlay.classList.add('show');
});

// Nascondi la sidebar e l’overlay
function closeSidebar() {
  sidebar.classList.remove('show');
  overlay.classList.remove('show');
}

// Nascondi cliccando sul pulsante "X"
closeSidebarBtn.addEventListener('click', closeSidebar);

// Nascondi cliccando sull’overlay
overlay.addEventListener('click', closeSidebar);
