async function getData() {
  const response = await fetch('http://165.232.180.53/getdata');
  const data = await response.json();
  data.reverse(); // Reverse the order of the array
  const tableBody = document.querySelector('#cardDataTable tbody');
  tableBody.innerHTML = '';
  data.forEach((item) => {
    const row = document.createElement('tr');
    const idCell = document.createElement('td');
    const uidCell = document.createElement('td');
    const timestampCell = document.createElement('td');
    idCell.textContent = item.id;
    uidCell.textContent = item.uid;
    timestampCell.textContent = new Date(item.timestamp).toLocaleString();
    row.appendChild(idCell);
    row.appendChild(uidCell);
    row.appendChild(timestampCell);
    tableBody.appendChild(row);
  });
}

getData();
setInterval(getData, 5000);